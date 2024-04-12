#include "includes.h"

void CFeatureHorrorAudio::Init()
{
	CChaosFeature::Init();
}

void CFeatureHorrorAudio::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	shm->speed = 48000;
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