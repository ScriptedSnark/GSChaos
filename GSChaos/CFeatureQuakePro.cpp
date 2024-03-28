#include "includes.h"

void CFeatureQuakePro::Init()
{
	CChaosFeature::Init();
}

void CFeatureQuakePro::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureQuakePro::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	(*sv_player)->v.fov = 0;
}

void CFeatureQuakePro::OnFrame(double time)
{
	if (!IsActive())
		return;

	// couldn't check if we're zooming so yeah
	(*sv_player)->v.fov = 150.f; // maybe it's supposed to be 110 but buh
}

const char* CFeatureQuakePro::GetFeatureName()
{
	return "Quake Pro";
}