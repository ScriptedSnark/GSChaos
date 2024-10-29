#include "includes.h"

void CFeatureViewOfsInsanity::Init()
{
	CChaosFeature::Init();
}

void CFeatureViewOfsInsanity::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	if (m_vecOldViewHeight == g_vecZero)
	{
		m_vecOldViewHeight = g_pRefParams->viewheight;
	}
}

void CFeatureViewOfsInsanity::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	if (m_vecOldViewHeight != g_vecZero)
	{
		*reinterpret_cast<Vector*>(g_pRefParams->viewheight) = m_vecOldViewHeight;
	}
}

void CFeatureViewOfsInsanity::V_CalcRefdef(struct ref_params_s* pparams)
{
	float currentTime = (float)gChaos.GetGlobalTime();

	float amplitude = 350.0f; // TODO: configure?
	float frequency = 5.0f; // TODO: configure?

	float zOffset = amplitude * sin(currentTime * frequency);

	pparams->viewheight[2] = zOffset;
}

const char* CFeatureViewOfsInsanity::GetFeatureName()
{
	return "View Offset Insanity";
}

double CFeatureViewOfsInsanity::GetDuration()
{
	return gChaos.GetChaosTime() * 0.4;
}

bool CFeatureViewOfsInsanity::UseCustomDuration()
{
	return true;
}