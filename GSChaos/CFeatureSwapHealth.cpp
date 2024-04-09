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
	(*sv_player)->v.armorvalue = min(health, 4000.0f); // 5000-5100 is crash point - StereoBucket
}

void CFeatureSwapHealth::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureSwapHealth::GetFeatureName()
{
	return "Swap health and armor";
}