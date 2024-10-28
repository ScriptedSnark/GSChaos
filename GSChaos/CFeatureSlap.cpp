#include "includes.h"

void CFeatureSlap::Init()
{
	CChaosFeature::Init();
}

void CFeatureSlap::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	UTIL_ScreenFade((*sv_player), Vector(255, 255, 255), 0.75f, 0.0f, 255, FFADE_IN);
	ChaosLoud::EmitSound(SND_SLAP);
	(*sv_player)->v.punchangle = Vector(-64.0f, -84.0f, 0.0f);
}

void CFeatureSlap::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureSlap::GetFeatureName()
{
	return "Slap";
}