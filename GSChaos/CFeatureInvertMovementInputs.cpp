#include "includes.h"

void CFeatureInvertMovementInputs::Init()
{
	CChaosFeature::Init();
}

void CFeatureInvertMovementInputs::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureInvertMovementInputs::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureInvertMovementInputs::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!IsActive())
		return;

	cmd->sidemove = -cmd->sidemove;
	cmd->forwardmove = -cmd->forwardmove;
}

const char* CFeatureInvertMovementInputs::GetFeatureName()
{
	return "Invert Movement Inputs";
}

double CFeatureInvertMovementInputs::GetDuration()
{
	return gChaos.GetChaosTime() * 0.77;
}

bool CFeatureInvertMovementInputs::UseCustomDuration()
{
	return true;
}

bool CFeatureInvertMovementInputs::CanBeInfinite()
{
	return true;
}