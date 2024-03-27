#include "includes.h"

bool g_bScientistMadness;

void CFeatureScientistMadness::Init()
{
	CChaosFeature::Init();
}

void CFeatureScientistMadness::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bScientistMadness = true;
}

void CFeatureScientistMadness::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bScientistMadness = false;
}

const char* CFeatureScientistMadness::GetFeatureName()
{
	return "Scientist Madness";
}