#include "includes.h"

void CFeatureThirdPerson::Init()
{
	CChaosFeature::Init();
}

void CFeatureThirdPerson::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	pEngfuncs->pfnClientCmd(";chaos_thirdperson;\n");
}

void CFeatureThirdPerson::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	bool bShouldDeactivate3rdPerson = true;
	for (CChaosFeature* i : gChaos.m_activeFeatures)
	{
		if (!stricmp(i->GetFeatureName(), "2D Camera"))
		{
			bShouldDeactivate3rdPerson = false;
			break;
		}
	}

	if (bShouldDeactivate3rdPerson)
		pEngfuncs->pfnClientCmd(";chaos_firstperson;\n");
}

const char* CFeatureThirdPerson::GetFeatureName()
{
	return "Third person";
}

double CFeatureThirdPerson::GetDuration()
{
	return gChaos.GetChaosTime() * 1.5;
}

bool CFeatureThirdPerson::UseCustomDuration()
{
	return true;
}