#include "includes.h"

std::vector<const char*> g_baseWeaponList =
{
	"weapon_357",
	"weapon_9mmAR",
	"weapon_9mmhandgun",
	"weapon_crossbow",
	"weapon_crowbar",
	"weapon_egon",
	"weapon_gauss",
	"weapon_glock", // duplicate
	"weapon_handgrenade",
	"weapon_hornetgun",
	"weapon_mp5", // duplicate
	"weapon_python", // duplicate
	"weapon_rpg",
	"weapon_satchel",
	"weapon_shotgun",
	"weapon_snark",
	"weapon_tripmine"
};

void CFeatureGiveRandomWeapon::Init()
{
	CChaosFeature::Init();

	m_pszWeaponName = nullptr;
}

void CFeatureGiveRandomWeapon::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	if (g_szExportedWeaponList.empty())
		g_szExportedWeaponList = g_baseWeaponList;

	int i = gChaos.GetRandomValue(0, g_szExportedWeaponList.size() - 1);
	edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING(g_szExportedWeaponList[i]));
	if (!pent)
		return;

	m_pszWeaponName = g_szExportedWeaponList[i];

	Vector origin = (*sv_player)->v.origin;
	pent->v.origin = origin;
	gEntityInterface->pfnSpawn(pent);
	gEntityInterface->pfnTouch(pent, (*sv_player));
	gEntityInterface->pfnTouch((*sv_player), pent);
}

void CFeatureGiveRandomWeapon::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_pszWeaponName = nullptr;
}

const char* CFeatureGiveRandomWeapon::GetFeatureName()
{
	if (m_pszWeaponName)
		return UTIL_VarArgs("Give random weapon (%s)", m_pszWeaponName);

	return "Give random weapon";
}

bool CFeatureGiveRandomWeapon::IsGood()
{
	return true;
}