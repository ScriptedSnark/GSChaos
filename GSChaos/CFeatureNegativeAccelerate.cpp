#include "includes.h"

void CFeatureNegativeAccelerate::Init()
{
	CChaosFeature::Init();
}

void CFeatureNegativeAccelerate::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	sv_accelerate = g_engfuncs->pfnCVarGetPointer("sv_accelerate");

	if (!sv_accelerate)
		return;

	m_flOldAccelerateValue = sv_accelerate->value;
	sv_accelerate->value = -m_flOldAccelerateValue;
}

void CFeatureNegativeAccelerate::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	if (!sv_accelerate)
	{
		SERVER_COMMAND(";sv_accelerate 10;\n");
		return;
	}

	sv_accelerate->value = m_flOldAccelerateValue;
}

void CFeatureNegativeAccelerate::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (!sv_accelerate)
		return;

	sv_accelerate->value = -m_flOldAccelerateValue;
}

const char* CFeatureNegativeAccelerate::GetFeatureName()
{
	return "Negative Accelerate";
}