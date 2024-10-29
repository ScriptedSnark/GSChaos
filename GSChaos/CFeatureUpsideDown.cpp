#include "includes.h"

void CFeatureUpsideDown::Init()
{
	CChaosFeature::Init();
}

void CFeatureUpsideDown::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;
}

void CFeatureUpsideDown::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	Vector viewAngles;
	pEngfuncs->GetViewAngles(viewAngles);
	viewAngles.z = 0;
	pEngfuncs->SetViewAngles(viewAngles);
}

void CFeatureUpsideDown::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	Vector viewAngles;
	pEngfuncs->GetViewAngles(viewAngles);
	viewAngles.z = 180;
	pEngfuncs->SetViewAngles(viewAngles);
}

const char* CFeatureUpsideDown::GetFeatureName()
{
	return "Upside Down";
}

double CFeatureUpsideDown::GetDuration()
{
	return gChaos.GetChaosTime() * 0.75;
}

bool CFeatureUpsideDown::UseCustomDuration()
{
	return true;
}

bool CFeatureUpsideDown::CanBeInfinite()
{
	return true;
}