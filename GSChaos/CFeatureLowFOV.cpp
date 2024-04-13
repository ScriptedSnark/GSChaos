#include "includes.h"

void CFeatureLowFOV::Init()
{
	CChaosFeature::Init();
}

const char* CFeatureLowFOV::GetFeatureName()
{
	return "Low FOV";
}

float CFeatureLowFOV::GetFOV()
{
	return 50.0f;
}