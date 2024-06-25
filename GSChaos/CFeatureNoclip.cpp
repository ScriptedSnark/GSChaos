#include "includes.h"

void CFeatureNoclip::Init()
{
	CChaosFeature::Init();
}

void CFeatureNoclip::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	(*sv_player)->v.movetype = MOVETYPE_NOCLIP;
}

void CFeatureNoclip::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	(*sv_player)->v.movetype = MOVETYPE_WALK;
}

const char* CFeatureNoclip::GetFeatureName()
{
	return "Get Noclip";
}

void CFeatureNoclip::ResetStates()
{
	if ((*sv_player)->v.movetype == MOVETYPE_NOCLIP)
		(*sv_player)->v.movetype = MOVETYPE_WALK;
}

double CFeatureNoclip::GetDuration()
{
	return gChaos.GetChaosTime() * 0.4;
}

bool CFeatureNoclip::UseCustomDuration()
{
	return true;
}

bool CFeatureNoclip::IsGood()
{
	return true;
}