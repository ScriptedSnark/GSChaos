#include "includes.h"

void CFeatureAmIDead::Init()
{
	CChaosFeature::Init();
}

void CFeatureAmIDead::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureAmIDead::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	Vector viewAngles;
	pEngfuncs->GetViewAngles(viewAngles);
	viewAngles.z = 0;
	pEngfuncs->SetViewAngles(viewAngles);
}

void CFeatureAmIDead::OnFrame(double time)
{
	if (!IsActive())
		return;

	Vector viewAngles;
	pEngfuncs->GetViewAngles(viewAngles);
	viewAngles.z = 80; // dead view angle
	pEngfuncs->SetViewAngles(viewAngles);
}

const char* CFeatureAmIDead::GetFeatureName()
{
	return "Am I dead?";
}

double CFeatureAmIDead::GetDuration()
{
	return gChaos.GetChaosTime() * 0.9;
}

bool CFeatureAmIDead::UseCustomDuration()
{
	return true;
}

bool CFeatureAmIDead::CanBeInfinite()
{
	return true;
}