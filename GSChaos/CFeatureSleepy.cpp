#include "includes.h"

#define SLEEPY_TIME			3.0

void CFeatureSleepy::Init()
{
	CChaosFeature::Init();
}

void CFeatureSleepy::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;

	m_flSleepyTime = gChaos.GetGlobalTime() + SLEEPY_TIME;
}

void CFeatureSleepy::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	UTIL_ScreenFade((*sv_player), Vector(0, 0, 0), 0.0f, 0.0f, 0, 0);
}

void CFeatureSleepy::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (gChaos.GetGlobalTime() > m_flSleepyTime)
	{
		UTIL_ScreenFade((*sv_player), Vector(0, 0, 0), 1.75f, 0.1f, 255, FFADE_IN);
		m_flSleepyTime = gChaos.GetGlobalTime() + SLEEPY_TIME;
	}
}

const char* CFeatureSleepy::GetFeatureName()
{
	return "Sleepy";
}

double CFeatureSleepy::GetDuration()
{
	return gChaos.GetChaosTime() * 1.5;
}

bool CFeatureSleepy::UseCustomDuration()
{
	return true;
}

bool CFeatureSleepy::CanBeInfinite()
{
	return true;
}