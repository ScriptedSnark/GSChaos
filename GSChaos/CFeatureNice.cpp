#include "includes.h"

void CFeatureNice::Init()
{
	CChaosFeature::Init();
}

void CFeatureNice::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.health = (*sv_player)->v.armorvalue = 69.0f;
}

void CFeatureNice::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureNice::GetFeatureName()
{
	return "Nice";
}