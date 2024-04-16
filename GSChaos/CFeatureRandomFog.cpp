#include "includes.h"

void CFeatureRandomFog::Init()
{
	CChaosFeature::Init();
}

void CFeatureRandomFog::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	InitFog();
}

void CFeatureRandomFog::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	DisableFog();
}

const char* CFeatureRandomFog::GetFeatureName()
{
	return "Random fog";
}

double CFeatureRandomFog::GetDuration()
{
	return gChaos.GetChaosTime() * 3.0;
}

bool CFeatureRandomFog::UseCustomDuration()
{
	return true;
}