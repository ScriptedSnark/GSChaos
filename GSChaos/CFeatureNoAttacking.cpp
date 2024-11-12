#include "includes.h"

void CFeatureNoAttacking::Init()
{
	CChaosFeature::Init();
}

void CFeatureNoAttacking::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureNoAttacking::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureNoAttacking::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!IsActive())
		return;

	cmd->buttons &= ~IN_ATTACK;
	cmd->buttons &= ~IN_ATTACK2;
	cmd->buttons &= ~IN_ALT1;
}

const char* CFeatureNoAttacking::GetFeatureName()
{
	return "No Attacking";
}

double CFeatureNoAttacking::GetDuration()
{
	return gChaos.GetChaosTime() * 0.9;
}

bool CFeatureNoAttacking::UseCustomDuration()
{
	return true;
}

bool CFeatureNoAttacking::CanBeInfinite()
{
	return true;
}