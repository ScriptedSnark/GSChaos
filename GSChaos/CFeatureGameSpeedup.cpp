#include "includes.h"

const char* CFeatureGameSpeedup::GetFeatureName()
{
	return "Game Speedup";
}

float CFeatureGameSpeedup::GetTimescale()
{
	return 2.0f;
}

double CFeatureGameSpeedup::GetDuration()
{
	return gChaos.GetChaosTime() * 0.5;
}