#include "includes.h"

const char* CFeatureZeroGravity::GetFeatureName()
{
	return "Zero Gravity";
}

float CFeatureZeroGravity::GetGravityValue()
{
	return 0.0f;
}

double CFeatureZeroGravity::GetDuration()
{
	return gChaos.GetChaosTime() * 1.1;
}

bool CFeatureZeroGravity::UseCustomDuration()
{
	return true;
}