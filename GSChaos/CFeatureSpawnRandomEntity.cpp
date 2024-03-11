#include "includes.h"

std::vector<const char*> g_szEntityList =
{
	"monster_alien_controller",
	"monster_alien_grunt",
	"monster_alien_slave",
	"monster_apache",
	"monster_babycrab",
	"monster_barnacle",
	"monster_barney",
	"monster_barney_dead",
	"monster_bigmomma",
	"monster_bloater",
	"monster_bullchicken",
	"monster_cockroach",
	"monster_flyer_flock",
	"monster_gargantua",
	"monster_gman",
	"monster_grunt_repel",
	"monster_handgrenade",
	"monster_headcrab",
	"monster_hevsuit_dead",
	"monster_hgrunt_dead",
	"monster_houndeye",
	"monster_human_assassin",
	"monster_human_grunt",
	"monster_ichthyosaur",
	"monster_leech",
	"monster_miniturret",
	"monster_nihilanth",
	"monster_rat",
	"monster_scientist",
	"monster_scientist_dead",
	"monster_sentry",
	"monster_sitting_scientist",
	"monster_snark",
	"monster_tentacle",
	"monster_turret",
	"monster_zombie",
	"xen_hair",
	"xen_plantlight",
	"xen_spore_large",
	"xen_spore_medium",
	"xen_spore_small",
	"xen_tree"
};

void CFeatureSpawnRandomEntity::Init()
{
	CChaosFeature::Init();
	m_pszEntityName = nullptr;
}

void CFeatureSpawnRandomEntity::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	int i = gChaos.GetRandomValue(0, g_szEntityList.size() - 1);
	edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING(g_szEntityList[i]));
	if (!pent)
		return;

	m_pszEntityName = g_szEntityList[i];

	Vector origin = (*sv_player)->v.origin;
	pent->v.origin = origin + gpGlobals->v_forward * 128;
	gEntityInterface->pfnSpawn(pent);
}

void CFeatureSpawnRandomEntity::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_pszEntityName = nullptr;
}

const char* CFeatureSpawnRandomEntity::GetFeatureName()
{
	if (m_pszEntityName)
		return UTIL_VarArgs("Spawn random entity (%s)", m_pszEntityName);

	return "Spawn random entity";
}