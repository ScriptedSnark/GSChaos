#include "includes.h"

void CFeatureNothing::Init()
{
	CChaosFeature::Init();
}

void CFeatureNothing::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureNothing::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureNothing::GetFeatureName()
{
	return "Nothing";
}