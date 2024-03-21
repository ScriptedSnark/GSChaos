#include "includes.h"

void CFeatureStop::Init()
{
	CChaosFeature::Init();
}

void CFeatureStop::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.velocity = Vector(0, 0, 0);
}

void CFeatureStop::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureStop::GetFeatureName()
{
	return "Stop";
}