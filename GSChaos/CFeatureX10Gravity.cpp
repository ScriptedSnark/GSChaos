#include "includes.h"

const char* CFeatureX10Gravity::GetFeatureName()
{
	return "X10 Gravity";
}

float CFeatureX10Gravity::GetGravityValue()
{
	return 8000.0f;
}

double CFeatureX10Gravity::GetDuration()
{
	return gChaos.GetChaosTime() * 0.5;
}

bool CFeatureX10Gravity::UseCustomDuration()
{
	return true;
}