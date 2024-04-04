#include "includes.h"

void CFeatureHigh::Init()
{
	CChaosFeature::Init();
}

void CFeatureHigh::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedShader = true;
}

void CFeatureHigh::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedShader = false;
}

const char* CFeatureHigh::GetFeatureName()
{
	return "High";
}