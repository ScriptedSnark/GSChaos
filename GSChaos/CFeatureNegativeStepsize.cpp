#include "includes.h"

void CFeatureNegativeStepsize::Init()
{
	CChaosFeature::Init();
}

void CFeatureNegativeStepsize::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	sv_stepsize = g_engfuncs->pfnCVarGetPointer("sv_stepsize");

	if (!sv_stepsize)
		return;

	m_flOldStepsizeValue = sv_stepsize->value;
	sv_stepsize->value = -18.0f;
	m_bActivated = true;
}

void CFeatureNegativeStepsize::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	if (!sv_stepsize)
	{
		SERVER_COMMAND("sv_stepsize 18\n");
		return;
	}

	sv_stepsize->value = m_flOldStepsizeValue;
}

void CFeatureNegativeStepsize::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (!sv_stepsize)
		return;

	sv_stepsize->value = -18.0f;
}

const char* CFeatureNegativeStepsize::GetFeatureName()
{
	return "Negative Stepsize";
}