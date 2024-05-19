#include "includes.h"

void CFeatureNegativeStepsize::Init()
{
	CChaosFeature::Init();
	m_flOldStepsizeValue = 18.0f;
}

void CFeatureNegativeStepsize::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	sv_stepsize = g_engfuncs->pfnCVarGetPointer("sv_stepsize");

	if (!sv_stepsize)
	{
		SERVER_COMMAND(UTIL_VarArgs("sv_stepsize %.01f\n", GetStepsizeValue()));
		return;
	}

	m_flOldStepsizeValue = sv_stepsize->value;
	sv_stepsize->value = GetStepsizeValue();
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

	sv_stepsize->value = GetStepsizeValue();
}

const char* CFeatureNegativeStepsize::GetFeatureName()
{
	return "Negative Stepsize";
}

float CFeatureNegativeStepsize::GetStepsizeValue()
{
	return -18.0f;
}

void CFeatureNegativeStepsize::ResetStates()
{
	if (sv_stepsize && m_flOldStepsizeValue)
		sv_stepsize->value = m_flOldStepsizeValue;
	else
		SERVER_COMMAND("sv_stepsize 18\n");
}

double CFeatureNegativeStepsize::GetDuration()
{
	return gChaos.GetChaosTime() * 2.33;
}

bool CFeatureNegativeStepsize::UseCustomDuration()
{
	return true;
}