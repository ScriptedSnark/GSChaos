#include "includes.h"

void CFeatureGiveOneArmor::Init()
{
	CChaosFeature::Init();
}

void CFeatureGiveOneArmor::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.armorvalue += 1.0f;
	UTIL_ScreenFade((*sv_player), Vector(255, 160, 0), 0.5f, 0.1f, 128, FFADE_IN);
}

void CFeatureGiveOneArmor::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureGiveOneArmor::GetFeatureName()
{
	return "Give +1 armor";
}