#include "includes.h"

void CFeatureGodMode::Init()
{
	CChaosFeature::Init();
}

void CFeatureGodMode::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;
	(*sv_player)->v.flags |= FL_GODMODE;
}

void CFeatureGodMode::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;
	(*sv_player)->v.flags &= ~FL_GODMODE;
}

void CFeatureGodMode::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (!(*sv_player))
		return;

	(*sv_player)->v.flags |= FL_GODMODE;
}

const char* CFeatureGodMode::GetFeatureName()
{
	return "God Mode";
}

void CFeatureGodMode::ResetStates()
{
	if ((*sv_player)->v.flags & FL_GODMODE)
		(*sv_player)->v.flags &= ~FL_GODMODE;
}

double CFeatureGodMode::GetDuration()
{
	return gChaos.GetChaosTime() * 1.25;
}

bool CFeatureGodMode::UseCustomDuration()
{
	return true;
}

bool CFeatureGodMode::IsGood()
{
	return true;
}