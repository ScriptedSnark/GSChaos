#include "includes.h"

void CFeatureFiftyPercentDeath::Init()
{
	CFeatureOnePercentDeath::Init();
}

void CFeatureFiftyPercentDeath::ActivateFeature()
{
	CFeatureOnePercentDeath::ActivateFeature();
}

void CFeatureFiftyPercentDeath::DeactivateFeature()
{
	CFeatureOnePercentDeath::DeactivateFeature();
}

const char* CFeatureFiftyPercentDeath::GetFeatureName()
{
	return "50% chance of death";
}

bool CFeatureFiftyPercentDeath::ShouldKill()
{
	return (gChaos.GetRandomValue(1, 100) > 50);
}