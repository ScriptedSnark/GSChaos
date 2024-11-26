#include "includes.h"

void CFeatureSwapAttacks::Init()
{
	CChaosFeature::Init();
}

void CFeatureSwapAttacks::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureSwapAttacks::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureSwapAttacks::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!IsActive())
		return;
	unsigned short att2 = cmd->buttons & IN_ATTACK2, att1 = cmd->buttons & IN_ATTACK;

	cmd->buttons &= ~(IN_ATTACK | IN_ATTACK2);
	if (att1)
		cmd->buttons |= IN_ATTACK2;
	if (att2)
		cmd->buttons |= IN_ATTACK;
}

const char* CFeatureSwapAttacks::GetFeatureName()
{
	return "Swap Attack Buttons";
}

double CFeatureSwapAttacks::GetDuration()
{
	return gChaos.GetChaosTime() * (4.0/3.0);
}

bool CFeatureSwapAttacks::UseCustomDuration()
{
	return true;
}

bool CFeatureSwapAttacks::CanBeInfinite()
{
	return true;
}