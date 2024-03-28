#include "includes.h"

void CFeatureNoHUD::Init()
{
	CChaosFeature::Init();
}

void CFeatureNoHUD::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bDrawHUD = true;
}

void CFeatureNoHUD::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bDrawHUD = false;
}

const char* CFeatureNoHUD::GetFeatureName()
{
	return "No HUD";
}