#include "includes.h"

void CFeatureSqueakShephard::Init()
{
	CChaosFeature::Init();
}

void CFeatureSqueakShephard::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	SpawnSqueak();
}

void CFeatureSqueakShephard::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureSqueakShephard::GetFeatureName()
{
	return "Spawn Squeak Shephard";
}

edict_t* CFeatureSqueakShephard::SpawnSqueak()
{
	edict_t* squeak = CREATE_NAMED_ENTITY(MAKE_STRING("monster_snark"));
	if (!squeak)
		return NULL;

	gEntityInterface->pfnSpawn(squeak);

	SET_MODEL(squeak, "../chaos/shephard.mdl");
	SET_SIZE(squeak, (*sv_player)->v.mins, (*sv_player)->v.maxs);

	Vector playerOrigin = (*sv_player)->v.origin + gpGlobals->v_forward * 96;

	squeak->v.health = 50;
	squeak->v.origin = playerOrigin;

	return squeak;
}