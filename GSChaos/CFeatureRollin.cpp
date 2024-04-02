#include "includes.h"

bool g_bActivatedRollin;

void CFeatureRollin::Init()
{
	CChaosFeature::Init();
}

void CFeatureRollin::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedRollin = true;
}

void CFeatureRollin::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedRollin = false;

	Vector viewAngles;
	pEngfuncs->GetViewAngles(viewAngles);
	viewAngles.z = 0;
	pEngfuncs->SetViewAngles(viewAngles);
}

const char* CFeatureRollin::GetFeatureName()
{
	return "Rollin'";
}