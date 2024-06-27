#include "includes.h"

void CFeature10GoodEffects::Init()
{
	CChaosFeature::Init();
}

void CFeature10GoodEffects::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	for (CChaosFeature* feature : gChaosFeatures)
	{
		if (feature->IsGood())
			feature->ActivateFeature();
	}
}

void CFeature10GoodEffects::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	for (CChaosFeature* feature : gChaosFeatures)
	{
		if (feature->IsGood() && !feature->UseCustomDuration())
			feature->DeactivateFeature();
	}
}

const char* CFeature10GoodEffects::GetFeatureName()
{
	return "Let's not make it more chaotic :3";
}