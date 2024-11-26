#include "includes.h"

void CFeatureTwitchy::Init()
{
	CChaosFeature::Init();
}

void CFeatureTwitchy::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	startshoot = pEngfuncs->GetAbsoluteTime() + gChaos.GetRandomValue(0.2f, 3.0f);
	endshoot = startshoot + gChaos.GetRandomValue(0.0f, 0.25f);
}

void CFeatureTwitchy::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureTwitchy::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!IsActive())
		return;
	
	double time = pEngfuncs->GetAbsoluteTime();

	if (time >= startshoot)
	{
		cmd->buttons ^= IN_ATTACK;
	}
	if (time >= endshoot)
	{
		startshoot = 2 * time + gChaos.GetRandomValue(0.2f, 3.0f) - endshoot;
		endshoot = startshoot + gChaos.GetRandomValue(0.0f, 0.333f);
	}
}

const char* CFeatureTwitchy::GetFeatureName()
{
	return "Munition Incontinence";
}

double CFeatureTwitchy::GetDuration()
{
	return gChaos.GetChaosTime() * (4.0 / 3.0);
}

bool CFeatureTwitchy::UseCustomDuration()
{
	return true;
}

bool CFeatureTwitchy::CanBeInfinite()
{
	return true;
}