#include "includes.h"

bool g_bNoLoad = false;

void CFeatureNoSaveLoading::Init()
{
	CChaosFeature::Init();
}

void CFeatureNoSaveLoading::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bNoLoad = true;
}

void CFeatureNoSaveLoading::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bNoLoad = false;
}

const char* CFeatureNoSaveLoading::GetFeatureName()
{
	return "No Save Loading";
}

double CFeatureNoSaveLoading::GetDuration()
{
	return gChaos.GetChaosTime() * 1.14;
}

bool CFeatureNoSaveLoading::UseCustomDuration()
{
	return true;
}

bool CFeatureNoSaveLoading::CanBeInfinite()
{
	return true;
}