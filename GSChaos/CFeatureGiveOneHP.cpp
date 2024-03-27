#include "includes.h"

void CFeatureGiveOneHP::Init()
{
	CChaosFeature::Init();
}

void CFeatureGiveOneHP::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.health += 1.0f;
	UTIL_ScreenFade((*sv_player), Vector(0, 192, 0), 0.5f, 0.1f, 128, FFADE_IN);
}

void CFeatureGiveOneHP::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureGiveOneHP::GetFeatureName()
{
	return "Give +1 HP";
}