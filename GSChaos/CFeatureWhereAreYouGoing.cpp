#include "includes.h"

void CFeatureWhereAreYouGoing::Init()
{
	CChaosFeature::Init();
}

void CFeatureWhereAreYouGoing::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_vSavedOrigin = (*sv_player)->v.origin;
}

void CFeatureWhereAreYouGoing::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!sv->active)
		return;

	if (sv->state != ss_active)
		return;

	(*sv_player)->v.origin = m_vSavedOrigin;
}

void CFeatureWhereAreYouGoing::Restore()
{
	m_vSavedOrigin = (*sv_player)->v.origin;
}

void CFeatureWhereAreYouGoing::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_vSavedOrigin = g_vecZero;
}

const char* CFeatureWhereAreYouGoing::GetFeatureName()
{
	return "Where are you going?";
}

double CFeatureWhereAreYouGoing::GetDuration()
{
	return gChaos.GetChaosTime() * 0.25;
}

bool CFeatureWhereAreYouGoing::UseCustomDuration()
{
	return true;
}