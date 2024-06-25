#include "includes.h"

void CFeatureGiveAllWeapons::Init()
{
	CChaosFeature::Init();
}

void CFeatureGiveAllWeapons::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	for (const char* weapon : g_szExportedWeaponList)
	{
		if (!weapon)
			continue;

		if (!weapon[0])
			continue;

		edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING(weapon));
		if (!pent)
			continue;

		Vector origin = (*sv_player)->v.origin;
		pent->v.origin = origin;
		gEntityInterface->pfnSpawn(pent);
		gEntityInterface->pfnTouch(pent, (*sv_player));
		gEntityInterface->pfnTouch((*sv_player), pent);
	}
}

void CFeatureGiveAllWeapons::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureGiveAllWeapons::GetFeatureName()
{
	return "Give all weapons";
}

bool CFeatureGiveAllWeapons::IsGood()
{
	return true;
}