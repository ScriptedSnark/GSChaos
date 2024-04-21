#include "includes.h"

bool g_bActivatedHorrorAudio;

void CFeatureHorrorAudio::Init()
{
	CChaosFeature::Init();
}

void CFeatureHorrorAudio::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedHorrorAudio = true;
}

void CFeatureHorrorAudio::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedHorrorAudio = false;
}

const char* CFeatureHorrorAudio::GetFeatureName()
{
	return "Horror Audio";
}

double CFeatureHorrorAudio::GetDuration()
{
	return gChaos.GetChaosTime() * 0.95;
}

bool CFeatureHorrorAudio::UseCustomDuration()
{
	return true;
}