#include "includes.h"

void CFeatureBoost::Init()
{
	CChaosFeature::Init();
}

void CFeatureBoost::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.velocity *= 3.0f;
}

void CFeatureBoost::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureBoost::GetFeatureName()
{
	return "Boost";
}