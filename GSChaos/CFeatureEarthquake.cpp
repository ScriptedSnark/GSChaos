#include "includes.h"

void CFeatureEarthquake::Init()
{
	CChaosFeature::Init();
}

void CFeatureEarthquake::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureEarthquake::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureEarthquake::OnFrame(double time)
{
	if (!IsActive())
		return;
	
	UTIL_ScreenShake((*sv_player)->v.origin, 15.0f, 5.0f, 2.0f, 1000.0f);
}

const char* CFeatureEarthquake::GetFeatureName()
{
	return "Earthquake";
}

double CFeatureEarthquake::GetDuration()
{
	return gChaos.GetChaosTime() * 1.11;
}

bool CFeatureEarthquake::UseCustomDuration()
{
	return true;
}

bool CFeatureEarthquake::CanBeInfinite()
{
	return true;
}