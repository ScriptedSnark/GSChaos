#include "includes.h"

const char* CFeatureHalfGravity::GetFeatureName()
{
	return "Half-Gravity";
}

float CFeatureHalfGravity::GetGravityValue()
{
	return 400.0f; // let's pretend that 800 is const
}

double CFeatureHalfGravity::GetDuration()
{
	return gChaos.GetChaosTime() * 1.3;
}

bool CFeatureHalfGravity::UseCustomDuration()
{
	return true;
}