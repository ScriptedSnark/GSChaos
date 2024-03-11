#include "includes.h"

void CFeatureInvertVelocity::Init()
{
	CChaosFeature::Init();
}

void CFeatureInvertVelocity::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	Vector invertedVelocity = -(*sv_player)->v.velocity;
	(*sv_player)->v.velocity = invertedVelocity;
}

void CFeatureInvertVelocity::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureInvertVelocity::GetFeatureName()
{
	return "Invert Velocity";
}