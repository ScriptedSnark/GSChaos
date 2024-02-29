#include "includes.h"

void CFeatureDarkness::Init()
{
	CChaosFeature::Init();
}

void CFeatureDarkness::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	LIGHT_STYLE(0, "a");
}

void CFeatureDarkness::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	LIGHT_STYLE(0, "m");
}

const char* CFeatureDarkness::GetFeatureName()
{
	return "Darkness";
}