#include "includes.h"

void CFeatureMonsterWorldspawn::Init()
{
	CChaosFeature::Init();
}

void CFeatureMonsterWorldspawn::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	
	monster_worldspawn = CREATE_NAMED_ENTITY(MAKE_STRING("func_wall"));

	if (!monster_worldspawn)
	{
		DeactivateFeature();
		return;
	}

	SET_MODEL(monster_worldspawn, pEngfuncs->pfnGetLevelName());

	gEntityInterface->pfnSpawn(monster_worldspawn);

	monster_worldspawn->v.origin = (*sv_player)->v.origin;
	monster_worldspawn->v.solid = SOLID_BSP;
	monster_worldspawn->v.movetype = MOVETYPE_PUSH;
}

void CFeatureMonsterWorldspawn::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureMonsterWorldspawn::GetFeatureName()
{
	return "monster_worldspawn";
}

edict_t* CFeatureMonsterWorldspawn::GetWorldspawnEdict()
{
	return monster_worldspawn;
}