#include "includes.h"

void CFeatureGiveGauss::Init()
{
	CChaosFeature::Init();
}

void CFeatureGiveGauss::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("weapon_gauss"));
	if (!pent)
		return;

	pent->v.origin = (*sv_player)->v.origin;
	pent->v.angles = (*sv_player)->v.angles;
	gEntityInterface->pfnSpawn(pent);
	gEntityInterface->pfnTouch((*sv_player), pent);
	gEntityInterface->pfnTouch(pent, (*sv_player));
}

void CFeatureGiveGauss::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureGiveGauss::GetFeatureName()
{
	return "Give Gauss";
}