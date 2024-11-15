#include "includes.h"

void CFeatureComboTime::Init()
{
	CChaosFeature::Init();
}

void CFeatureComboTime::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	gChaos.EnableComboTime();
	gChaos.ResetChaosBarTimer();
}

void CFeatureComboTime::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureComboTime::GetFeatureName()
{
	return "COMBO TIME!!!";
}