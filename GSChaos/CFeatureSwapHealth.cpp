#include "includes.h"

void CFeatureSwapHealth::Init()
{
	CChaosFeature::Init();
}

void CFeatureSwapHealth::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	float health, armor;
	health = (*sv_player)->v.health;
	armor = (*sv_player)->v.armorvalue;

	(*sv_player)->v.health = max(1.0f, armor);
	(*sv_player)->v.armorvalue = health;
}

void CFeatureSwapHealth::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureSwapHealth::GetFeatureName()
{
	return "Swap health and armor";
}