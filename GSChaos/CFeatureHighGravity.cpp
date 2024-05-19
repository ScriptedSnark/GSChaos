#include "includes.h"

void CFeatureHighGravity::Init()
{
	CChaosFeature::Init();
}

void CFeatureHighGravity::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	sv_gravity = g_engfuncs->pfnCVarGetPointer("sv_gravity");

	if (!sv_gravity)
	{
		SERVER_COMMAND(UTIL_VarArgs("sv_gravity %.01f\n", GetGravityValue()));
		return;
	}

	m_flOldGravityValue = sv_gravity->value;
	m_bActivated = true;
}

void CFeatureHighGravity::DeactivateFeature()
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

void CFeatureHighGravity::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (!sv_gravity)
		return;

	sv_gravity->value = GetGravityValue();
}

const char* CFeatureHighGravity::GetFeatureName()
{
	return "X2 Gravity";
}

float CFeatureHighGravity::GetGravityValue()
{
	return 1600.0f;
}

void CFeatureHighGravity::ResetStates()
{
	if (sv_gravity && m_flOldGravityValue)
		sv_gravity->value = m_flOldGravityValue;
	else
		SERVER_COMMAND("sv_gravity 800\n");
}


double CFeatureHighGravity::GetDuration()
{
	return gChaos.GetChaosTime() * 0.75;
}

bool CFeatureHighGravity::UseCustomDuration()
{
	return true;
}