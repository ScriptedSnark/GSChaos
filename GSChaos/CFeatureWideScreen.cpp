#include "includes.h"

bool g_bActivatedWideScreen;

void CFeatureWideScreen::Init()
{
	CChaosFeature::Init();
}

void CFeatureWideScreen::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedWideScreen = true;
}

void CFeatureWideScreen::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedWideScreen = false;
}

const char* CFeatureWideScreen::GetFeatureName()
{
	return "\"It's easier to aim\", they said";
}

double CFeatureWideScreen::GetDuration()
{
	return gChaos.GetChaosTime() * 1.08;
}

bool CFeatureWideScreen::UseCustomDuration()
{
	return true;
}