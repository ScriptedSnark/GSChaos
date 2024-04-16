#include "includes.h"

float Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

void CFeatureGTA2Camera::Init()
{
	CChaosFeature::Init();
}

void CFeatureGTA2Camera::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	cam_idealdist = pEngfuncs->pfnGetCvarPointer("cam_idealdist");
	cam_idealyaw = pEngfuncs->pfnGetCvarPointer("cam_idealyaw");
	cam_idealpitch = pEngfuncs->pfnGetCvarPointer("cam_idealpitch");
	cl_pitchup = pEngfuncs->pfnGetCvarPointer("cl_pitchup");
	cl_pitchdown = pEngfuncs->pfnGetCvarPointer("cl_pitchdown");

	pEngfuncs->pfnClientCmd(";thirdperson;\n");

	cvar_values[0] = cam_idealdist->value;
	cvar_values[1] = cam_idealyaw->value;
	cvar_values[2] = cam_idealpitch->value;
	cvar_values[3] = cl_pitchup->value;
	cvar_values[4] = cl_pitchdown->value;

	cam_idealdist->value = 600.0f;
	cam_idealyaw->value = 0.0f;
	cam_idealpitch->value = 89.99f;
	cl_pitchup->value = -8.0f;
	cl_pitchdown->value = -8.0f;

	m_bActivated = true;
	m_bAnimating = true;

	ma_engine_play_sound(&miniAudio, "chaos/sci_respect.wav", NULL);
}

void CFeatureGTA2Camera::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	pEngfuncs->pfnClientCmd(";firstperson;\n");

	cam_idealdist->value = cvar_values[0];
	cam_idealyaw->value = cvar_values[1];
	cam_idealpitch->value = cvar_values[2];
	cl_pitchup->value = cvar_values[3];
	cl_pitchdown->value = cvar_values[4];
}

void CFeatureGTA2Camera::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (!m_bAnimating)
		return;
}

const char* CFeatureGTA2Camera::GetFeatureName()
{
	return "2D Camera";
}

double CFeatureGTA2Camera::GetDuration()
{
	return gChaos.GetChaosTime() * 1.0;
}

bool CFeatureGTA2Camera::UseCustomDuration()
{
	return true;
}