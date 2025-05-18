#include "includes.h"

void CFeatureFlashbang::Init()
{
	CChaosFeature::Init();
}

void CFeatureFlashbang::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	UTIL_ScreenFade((*sv_player), Vector(255, 255, 255), 3, 1.5f, 255, 0);
	pEngfuncs->pfnClientCmd(";spk ../../chaos/flashbang-1;\n");
}

void CFeatureFlashbang::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureFlashbang::GetFeatureName()
{
	return "Flashbang";
}