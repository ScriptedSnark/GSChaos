#include "includes.h"

void CFeatureGiveHealth::Init()
{
	CChaosFeature::Init();
}

void CFeatureGiveHealth::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.health += 100.0f;
	ma_engine_play_sound(&miniAudio, "valve/sound/items/smallmedkit1.wav", NULL);
	UTIL_ScreenFade((*sv_player), Vector(0, 192, 0), 1.25f, 0.1f, 192, FFADE_IN);
}

void CFeatureGiveHealth::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureGiveHealth::GetFeatureName()
{
	return "Give +100 HP";
}