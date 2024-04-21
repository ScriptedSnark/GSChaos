#include "includes.h"

volatile dma_t* shm;

void CFeatureAudioCorrupt::Init()
{
	CChaosFeature::Init();
}

void CFeatureAudioCorrupt::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;
}

void CFeatureAudioCorrupt::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	shm->speed = SOUND_11k;
}

void CFeatureAudioCorrupt::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	shm->speed = gChaos.GetRandomValue(10000, 14000);
}

const char* CFeatureAudioCorrupt::GetFeatureName()
{
	return "Audio Corrupt";
}

double CFeatureAudioCorrupt::GetDuration()
{
	return gChaos.GetChaosTime() * 0.15;
}

bool CFeatureAudioCorrupt::UseCustomDuration()
{
	return true;
}