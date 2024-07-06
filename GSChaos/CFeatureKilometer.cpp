#include "includes.h"

bool g_bActivatedKilometer = false;

void CFeatureKilometer::Init()
{
	CChaosFeature::Init();
}

void CFeatureKilometer::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedKilometer = true;
}

void CFeatureKilometer::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedKilometer = false;
}

const char* CFeatureKilometer::GetFeatureName()
{
	return "Kilometer";
}

double CFeatureKilometer::GetDuration()
{
	return gChaos.GetChaosTime() * 1.1;
}

bool CFeatureKilometer::UseCustomDuration()
{
	return true;
}