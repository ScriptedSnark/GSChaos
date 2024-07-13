#include "includes.h"

bool g_bActivatedChipmunks = false;

void CFeatureChipmunks::Init()
{
	CChaosFeature::Init();
}

void CFeatureChipmunks::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedChipmunks = true;
}

void CFeatureChipmunks::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedChipmunks = false;
}

const char* CFeatureChipmunks::GetFeatureName()
{
	return "Chipmunks";
}

double CFeatureChipmunks::GetDuration()
{
	return gChaos.GetChaosTime() * 1.36;
}

bool CFeatureChipmunks::UseCustomDuration()
{
	return true;
}