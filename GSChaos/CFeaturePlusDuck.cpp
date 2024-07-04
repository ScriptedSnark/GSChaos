#include "includes.h"

void CFeaturePlusDuck::Init()
{
	CChaosFeature::Init();
}

void CFeaturePlusDuck::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeaturePlusDuck::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeaturePlusDuck::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	cmd->buttons |= IN_DUCK;
}

const char* CFeaturePlusDuck::GetFeatureName()
{
	return "+duck";
}

double CFeaturePlusDuck::GetDuration()
{
	return gChaos.GetChaosTime() * 1.25;
}

bool CFeaturePlusDuck::UseCustomDuration()
{
	return true;
}