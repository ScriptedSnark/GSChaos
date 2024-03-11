#include "includes.h"

void CFeatureIceSkating::Init()
{
	CChaosFeature::Init();
}

void CFeatureIceSkating::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	sv_friction = g_engfuncs->pfnCVarGetPointer("sv_friction");

	if (!sv_friction)
		return;

	m_flOldFrictionValue = sv_friction->value;
	m_bActivated = true;
}

void CFeatureIceSkating::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	if (!sv_friction)
	{
		SERVER_COMMAND("sv_friction 4\n");
		return;
	}

	sv_friction->value = m_flOldFrictionValue;
}

void CFeatureIceSkating::OnFrame(double time)
{
	if (!m_bActivated || !sv_friction)
		return;

	sv_friction->value = 0.0f;
}

const char* CFeatureIceSkating::GetFeatureName()
{
	return "Ice skating";
}