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