#include "includes.h"

const char* CFeatureStandstill::GetFeatureName()
{
	return "Standstill (1% game speed)";
}

float CFeatureStandstill::GetTimescale()
{
	return 0.01f;
}

double CFeatureStandstill::GetDuration()
{
	return gChaos.GetChaosTime() * 0.1;
}