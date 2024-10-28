#include "includes.h"

void CFeatureTakeOneHP::Init()
{
	CChaosFeature::Init();
}

void CFeatureTakeOneHP::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	UTIL_TakeDamage((*sv_player)->v, 1.0f, DMG_GENERIC);
	UTIL_ScreenFade((*sv_player), Vector(192, 0, 0), 0.5f, 0.1f, 128, FFADE_IN);
	ChaosLoud::EmitSound(SND_PAIN);
}

void CFeatureTakeOneHP::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureTakeOneHP::GetFeatureName()
{
	return "Take 1 HP";
}