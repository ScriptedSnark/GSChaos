#include "includes.h"

void CFeatureLowDrawDistance::Init()
{
	CChaosFeature::Init();
}

void CFeatureLowDrawDistance::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	sv_zmax = pEngfuncs->pfnGetCvarPointer("sv_zmax");

	if (sv_zmax)
		m_iOldZMaxValue = sv_zmax->value;
	else
		CChaosFeature::DeactivateFeature();
}

void CFeatureLowDrawDistance::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	if (sv_zmax)
	{
		sv_zmax->value = (m_iOldZMaxValue == 0) ? 8192.0f : m_iOldZMaxValue;
	}
}

void CFeatureLowDrawDistance::OnFrame(double time)
{
	if (!IsActive())
		return;
	
	if (sv_zmax)
		sv_zmax->value = 300.0f;
}

const char* CFeatureLowDrawDistance::GetFeatureName()
{
	return "Low Draw Distance";
}

double CFeatureLowDrawDistance::GetDuration()
{
	return gChaos.GetChaosTime() * 0.79;
}

bool CFeatureLowDrawDistance::UseCustomDuration()
{
	return true;
}

bool CFeatureLowDrawDistance::CanBeInfinite()
{
	return true;
}