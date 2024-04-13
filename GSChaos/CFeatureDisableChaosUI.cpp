#include "includes.h"

void CFeatureDisableChaosUI::Init()
{
	CChaosFeature::Init();
}

void CFeatureDisableChaosUI::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bDisableChaosUI = true;
}

void CFeatureDisableChaosUI::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bDisableChaosUI = false;
}

const char* CFeatureDisableChaosUI::GetFeatureName()
{
	return "Disable Chaos UI";
}