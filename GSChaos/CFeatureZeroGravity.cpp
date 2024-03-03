#include "includes.h"

void CFeatureZeroGravity::Init()
{
	CChaosFeature::Init();
}

void CFeatureZeroGravity::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	sv_gravity = g_engfuncs->pfnCVarGetPointer("sv_gravity");

	if (!sv_gravity)
		return;

	m_flOldGravityValue = sv_gravity->value;
	m_bActivated = true;
}

void CFeatureZeroGravity::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	if (!sv_gravity)
	{
		SERVER_COMMAND("sv_gravity 800\n");
		return;
	}

	sv_gravity->value = m_flOldGravityValue;
}

void CFeatureZeroGravity::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (!sv_gravity)
		return;

	sv_gravity->value = 0.0f;
}

const char* CFeatureZeroGravity::GetFeatureName()
{
	return "Zero Gravity";
}