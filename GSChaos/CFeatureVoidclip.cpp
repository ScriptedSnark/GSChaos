#include "includes.h"

Vector g_vecSavedVelocity = g_vecZero;

void CFeatureVoidclip::Init()
{
	CChaosFeature::Init();
}

void CFeatureVoidclip::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	g_vecSavedVelocity = (*sv_player)->v.velocity;
}

void CFeatureVoidclip::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureVoidclip::OnFrame(double time)
{
	if (!IsActive())
		return;
	
	if (g_vecSavedVelocity.Length2D() < 50)
	{
		(*sv_player)->v.origin.z -= (128 * ImGui::GetIO().DeltaTime);
	}
	else
	{
		(*sv_player)->v.origin += (g_vecSavedVelocity * ImGui::GetIO().DeltaTime);
		(*sv_player)->v.velocity = g_vecZero;
	}
}

const char* CFeatureVoidclip::GetFeatureName()
{
	return "Voidclip";
}

double CFeatureVoidclip::GetDuration()
{
	return gChaos.GetChaosTime() * 0.08;
}

bool CFeatureVoidclip::UseCustomDuration()
{
	return true;
}