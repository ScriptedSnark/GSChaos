#include "includes.h"

void CFeatureWaterPush::Init()
{
	CChaosFeature::Init();
}

void CFeatureWaterPush::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureWaterPush::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureWaterPush::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (sv->state != ss_active)
		return;

	if ((*sv_player)->v.flags & FL_INWATER)
		(*sv_player)->v.velocity.z += 25.0f;
}

const char* CFeatureWaterPush::GetFeatureName()
{
	return "Water Push";
}

double CFeatureWaterPush::GetDuration()
{
	return gChaos.GetChaosTime() * 1.12;
}

bool CFeatureWaterPush::UseCustomDuration()
{
	return true;
}

bool CFeatureWaterPush::CanBeInfinite()
{
	return true;
}