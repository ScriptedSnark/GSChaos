#include "includes.h"

void CFeatureGiveArmor::Init()
{
	CChaosFeature::Init();
}

void CFeatureGiveArmor::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.armorvalue += 100.0f;
	ChaosLoud::EmitSound(SND_SUITCHARGEOK);
	UTIL_ScreenFade((*sv_player), Vector(255, 160, 0), 1.25f, 0.1f, 192, FFADE_IN);
}

void CFeatureGiveArmor::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureGiveArmor::GetFeatureName()
{
	return "Give +100 armor";
}

bool CFeatureGiveArmor::IsGood()
{
	return true;
}