#include "includes.h"

void CFeatureHighGravity::Init()
{
	CChaosFeature::Init();
}

void CFeatureHighGravity::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	SERVER_COMMAND("sv_gravity 1600\n");
}

void CFeatureHighGravity::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	SERVER_COMMAND("sv_gravity 800\n");
}

const char* CFeatureHighGravity::GetFeatureName()
{
	return "X2 Gravity";
}