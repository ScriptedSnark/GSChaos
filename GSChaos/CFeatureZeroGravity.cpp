#include "includes.h"

void CFeatureZeroGravity::Init()
{
	CChaosFeature::Init();
}

void CFeatureZeroGravity::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	SERVER_COMMAND("sv_gravity 0\n");
}

void CFeatureZeroGravity::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	SERVER_COMMAND("sv_gravity 800\n");
}

const char* CFeatureZeroGravity::GetFeatureName()
{
	return "Zero Gravity";
}