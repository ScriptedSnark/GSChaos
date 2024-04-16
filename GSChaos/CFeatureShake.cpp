#include "includes.h"

void CFeatureShake::Init()
{
	CChaosFeature::Init();
}

void CFeatureShake::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureShake::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureShake::OnFrame(double time)
{
	if (!IsActive())
		return;

	(*sv_player)->v.punchangle = Vector(gChaos.GetRandomValue(-1.0f, 2.0f), gChaos.GetRandomValue(-1.0f, 2.0f), gChaos.GetRandomValue(-1.0f, 2.0f));
}

const char* CFeatureShake::GetFeatureName()
{
	return "Shake";
}

double CFeatureShake::GetDuration()
{
	return gChaos.GetChaosTime() * 1.0;
}

bool CFeatureShake::UseCustomDuration()
{
	return true;
}