#include "includes.h"

void CFeatureQuakePro::Init()
{
	CChaosFeature::Init();

	default_fov = pEngfuncs->pfnGetCvarPointer("default_fov");

	if (!default_fov)
		return;

	m_flOldFOVValue = default_fov->value;
}

void CFeatureQuakePro::ActivateFeature()
{
	// do it before actual activating
	bool bShouldSaveFOV = true;
	for (auto& i : gChaos.m_activeFeatures)
	{
		if (!stricmp(i->GetFeatureName(), "Quake Pro") || !stricmp(i->GetFeatureName(), "Low FOV"))
		{
			bShouldSaveFOV = false;
		}
	}

	CChaosFeature::ActivateFeature();

	default_fov = pEngfuncs->pfnGetCvarPointer("default_fov");

	if (!default_fov)
		return;

	if (bShouldSaveFOV)
		m_flOldFOVValue = default_fov->value;

	default_fov->value = GetFOV();
}

void CFeatureQuakePro::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	(*sv_player)->v.fov = 0;

	if (!default_fov)
		return;

	default_fov->value = m_flOldFOVValue;
}

void CFeatureQuakePro::OnFrame(double time)
{
	if (!IsActive())
		return;

	(*sv_player)->v.fov = GetFOV();

	if (!default_fov)
		return;

	default_fov->value = GetFOV();
}

const char* CFeatureQuakePro::GetFeatureName()
{
	return "Quake Pro";
}

float CFeatureQuakePro::GetFOV()
{
	return 150.0f;
}

double CFeatureQuakePro::GetDuration()
{
	return gChaos.GetChaosTime() * 1.75;
}

bool CFeatureQuakePro::UseCustomDuration()
{
	return true;
}