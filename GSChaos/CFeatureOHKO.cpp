#include "includes.h"

void CFeatureOHKO::Init()
{
	CChaosFeature::Init();
}

void CFeatureOHKO::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureOHKO::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureOHKO::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!IsActive())
		return;
	
	// need to do this in CL_CreateMove because OnFrame is not so reliable
	(*sv_player)->v.health = min((*sv_player)->v.health, 1.0f);
	(*sv_player)->v.armorvalue = 0.0f;
}

const char* CFeatureOHKO::GetFeatureName()
{
	return "One Hit KO";
}

double CFeatureOHKO::GetDuration()
{
	return gChaos.GetChaosTime() * 1.04;
}

bool CFeatureOHKO::UseCustomDuration()
{
	return true;
}

bool CFeatureOHKO::CanBeInfinite()
{
	return true;
}