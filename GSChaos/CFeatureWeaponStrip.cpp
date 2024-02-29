#include "includes.h"

void CFeatureWeaponStrip::Init()
{
	CChaosFeature::Init();
}

void CFeatureWeaponStrip::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("player_weaponstrip"));
	if (!pent)
		return;

	pent->v.origin = (*sv_player)->v.origin;
	pent->v.angles = (*sv_player)->v.angles;
	gEntityInterface->pfnUse(pent, (*sv_player));
}

void CFeatureWeaponStrip::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureWeaponStrip::GetFeatureName()
{
	return "player_weaponstrip";
}