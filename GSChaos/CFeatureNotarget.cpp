#include "includes.h"

void CFeatureNotarget::Init()
{
	CChaosFeature::Init();
}

void CFeatureNotarget::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	(*sv_player)->v.flags |= FL_NOTARGET;
}

void CFeatureNotarget::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	(*sv_player)->v.flags &= ~FL_NOTARGET;
}

void CFeatureNotarget::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (!(*sv_player))
		return;

	(*sv_player)->v.flags |= FL_NOTARGET;
}

void CFeatureNotarget::ResetStates()
{
	if ((*sv_player)->v.flags & FL_NOTARGET)
		(*sv_player)->v.flags &= ~FL_NOTARGET;
}

const char* CFeatureNotarget::GetFeatureName()
{
	return "Notarget";
}