#include "includes.h"

extern float* sys_timescale;

void CFeatureHalfGameSpeed::Init()
{
	CChaosFeature::Init();
}

void CFeatureHalfGameSpeed::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureHalfGameSpeed::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	*sys_timescale = 1.0f;
}

void CFeatureHalfGameSpeed::OnFrame(double time)
{
	if (!IsActive())
		return;

	*sys_timescale = GetTimescale();
}

const char* CFeatureHalfGameSpeed::GetFeatureName()
{
	return "Half Game Speed";
}

double CFeatureHalfGameSpeed::GetDuration()
{
	return gChaos.GetChaosTime() * 1.15;
}

bool CFeatureHalfGameSpeed::UseCustomDuration()
{
	return true;
}

float CFeatureHalfGameSpeed::GetTimescale()
{
	return 0.5f;
}