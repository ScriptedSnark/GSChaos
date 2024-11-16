#include "includes.h"

double delay = 0.25;
void CFeatureInputDelay::Init()
{
	CChaosFeature::Init();
}

void CFeatureInputDelay::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_first = true;
	m_vfirst = true;

	cl_pitchup = pEngfuncs->pfnGetCvarPointer("cl_pitchup");
	cl_pitchdown = pEngfuncs->pfnGetCvarPointer("cl_pitchdown");
}

void CFeatureInputDelay::DeactivateFeature()
{
	m_first = false;
	m_vfirst = false;
	std::queue<usercmd_time_s>().swap(m_commandQueue);
	std::queue<viewangles_time_s>().swap(m_viewQueue);
	CChaosFeature::DeactivateFeature();
}

static void VectorCopy(float* in, float* out)
{
	out[0] = in[0];
	out[1] = in[1];
	out[2] = in[2];
}

static void VectorSub(float* in, float* out)
{
	out[0] -= in[0];
	out[1] -= in[1];
	out[2] -= in[2];
}

static void VectorAdd(float* in, float* out)
{
	out[0] += in[0];
	out[1] += in[1];
	out[2] += in[2];
}
// Taken from pm_shared / pm_math.c 
static float anglemod(float a)
{
	a = (360.0 / 65536) * ((int)(a * (65536 / 360.0)) & 65535);
	return a;
}

void CFeatureInputDelay::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	// Remember first input until buffer fills up to delay threshold.
	if (m_first)
	{
		m_lastcmd = *cmd;
		m_lastcmd.impulse = 0; 
		m_first = false;
		return;
	}

	double time = pEngfuncs->GetAbsoluteTime();
	// Queue up a copy of cmd and when it happened
	m_commandQueue.push(usercmd_time_s{ *cmd, time });

	// Not sure what the best way to do this is, but I think I'll just drop inputs if
	// too many happen to hit the delay threshold (fps change, menu buffering)
	while (!m_commandQueue.empty() && m_commandQueue.front().time + delay <= time)
	{
		m_lastcmd = m_commandQueue.front().cmd;
		m_commandQueue.pop();
	}

	*cmd = m_lastcmd;
	// reset impulse if the same cmd is applied twice
	m_lastcmd.impulse = 0;

	float cangles[3];
	pEngfuncs->GetViewAngles(cangles);
	// I think I want to preserve roll, from other effects.
	float roll = cangles[2];
	// same as with cmd buffering
	if (m_vfirst)
	{
		VectorCopy(cangles, m_lastview);
		m_vfirst = false;
		return;
	}
	// We're gonna buffer angle deltas instead and reapply them later
	VectorSub(m_lastview, cangles);

	m_viewQueue.push(viewangles_time_s{ {cangles[0], cangles[1], cangles[2]},  time });

	while (!m_viewQueue.empty() && m_viewQueue.front().time + delay <= time)
	{
		// Copy and apply the delta to the view.
		VectorCopy(m_viewQueue.front().vangles, cangles);
		VectorAdd(cangles, m_lastview);
		// same as in client sdk
		m_lastview[1] = anglemod(m_lastview[1]);

		if (m_lastview[0] > cl_pitchdown->value)
			m_lastview[0] = cl_pitchdown->value;
		if (m_lastview[0] < -cl_pitchup->value)
			m_lastview[0] = -cl_pitchup->value;
		m_viewQueue.pop();
	}
	m_lastview[2] = roll;
	pEngfuncs->SetViewAngles(m_lastview);

	VectorCopy(m_lastview, cmd->viewangles);
}

void CFeatureInputDelay::Restore()
{
	m_vfirst = true;
	std::queue<viewangles_time_s>().swap(m_viewQueue);
}
void CFeatureInputDelay::VidInit() 
{
	m_vfirst = true;
	std::queue<viewangles_time_s>().swap(m_viewQueue);
}

const char* CFeatureInputDelay::GetFeatureName()
{
	return "Cloud Gaming";
}

double CFeatureInputDelay::GetDuration()
{
	return gChaos.GetChaosTime() * 1.25;
}

bool CFeatureInputDelay::UseCustomDuration()
{
	return true;
}

bool CFeatureInputDelay::CanBeInfinite()
{
	return true;
}