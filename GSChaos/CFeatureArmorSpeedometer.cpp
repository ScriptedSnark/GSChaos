#include "includes.h"

void CFeatureArmorSpeedometer::Init()
{
	CChaosFeature::Init();
}

void CFeatureArmorSpeedometer::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureArmorSpeedometer::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureArmorSpeedometer::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!(*sv_player))
		return;

	if (sv && sv->state != ss_active)
		return;

	// You can actually get crash if you're too fast xdd
	(*sv_player)->v.armorvalue = (*sv_player)->v.velocity.Length2D();
}

const char* CFeatureArmorSpeedometer::GetFeatureName()
{
	return "Armor Speedometer";
}

double CFeatureArmorSpeedometer::GetDuration()
{
	return gChaos.GetChaosTime() * 1.05;
}

bool CFeatureArmorSpeedometer::UseCustomDuration()
{
	return true;
}

bool CFeatureArmorSpeedometer::CanBeInfinite()
{
	return true;
}