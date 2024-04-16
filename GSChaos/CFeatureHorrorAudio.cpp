#include "includes.h"

void CFeatureHorrorAudio::Init()
{
	CChaosFeature::Init();
}

void CFeatureHorrorAudio::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	shm->speed = 44100;
}

void CFeatureHorrorAudio::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	shm->speed = SOUND_11k;
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