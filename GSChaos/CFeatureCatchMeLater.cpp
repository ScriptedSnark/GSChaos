#include "includes.h"

bool g_bActivatedBarneyBeer = false;

void CFeatureCatchMeLater::Init()
{
	CChaosFeature::Init();
}

void CFeatureCatchMeLater::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedBarneyBeer = true;
}

void CFeatureCatchMeLater::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedBarneyBeer = false;
}

const char* CFeatureCatchMeLater::GetFeatureName()
{
	return "Catch me later";
}

double CFeatureCatchMeLater::GetDuration()
{
	return gChaos.GetChaosTime() * 1.31;
}

bool CFeatureCatchMeLater::UseCustomDuration()
{
	return true;
}

bool CFeatureCatchMeLater::CanBeInfinite()
{
	return true;
}