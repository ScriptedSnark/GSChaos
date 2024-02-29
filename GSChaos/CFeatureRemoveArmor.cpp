#include "includes.h"

void CFeatureRemoveArmor::Init()
{
	CChaosFeature::Init();
}

void CFeatureRemoveArmor::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.armorvalue = 0.0f;
}

void CFeatureRemoveArmor::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureRemoveArmor::GetFeatureName()
{
	return "Remove Armor";
}