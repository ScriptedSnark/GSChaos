#include "includes.h"

bool g_bActivatedViewDistortion = false;

void CFeatureViewDistortion::Init()
{
	CChaosFeature::Init();
}

void CFeatureViewDistortion::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedViewDistortion = true;
}

void CFeatureViewDistortion::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedViewDistortion = false;
}

const char* CFeatureViewDistortion::GetFeatureName()
{
	return "View Distortion";
}

double CFeatureViewDistortion::GetDuration()
{
	return gChaos.GetChaosTime() * 0.745;
}

bool CFeatureViewDistortion::UseCustomDuration()
{
	return true;
}