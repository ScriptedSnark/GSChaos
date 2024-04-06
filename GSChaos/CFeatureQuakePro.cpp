#include "includes.h"

void CFeatureQuakePro::Init()
{
	CChaosFeature::Init();
}

void CFeatureQuakePro::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	default_fov = pEngfuncs->pfnGetCvarPointer("default_fov");

	if (!default_fov)
		return;

	m_flOldFOVValue = default_fov->value;
	default_fov->value = 150.f;
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

	// couldn't check if we're zooming so yeah
	(*sv_player)->v.fov = 150.f; // maybe it's supposed to be 110 but buh

	if (!default_fov)
		return;

	default_fov->value = 150.f;
}

const char* CFeatureQuakePro::GetFeatureName()
{
	return "Quake Pro";
}