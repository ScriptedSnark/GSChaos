#include "includes.h"

void CFeatureDisableChaosUI::Init()
{
	CChaosFeature::Init();
}

void CFeatureDisableChaosUI::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bDisableChaosUI = true;

	pEngfuncs->pfnClientCmd(";say \"Where's my Chaos UI??? :o\";");
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

double CFeatureDisableChaosUI::GetDuration()
{
	return gChaos.GetChaosTime() * 2.0;
}

bool CFeatureDisableChaosUI::UseCustomDuration()
{
	return true;
}