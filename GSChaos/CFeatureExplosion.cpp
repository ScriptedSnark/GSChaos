#include "includes.h"

void CFeatureExplosion::Init()
{
	CChaosFeature::Init();
}

void CFeatureExplosion::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("rpg_rocket"));
	if (!pent)
		return;

	pent->v.origin = (*sv_player)->v.origin;
	pent->v.angles = (*sv_player)->v.angles;
	pent->v.dmg = 100;
	pent->v.dmgtime = 1.0f;
	pent->v.nextthink = gpGlobals->time + 0.1f;
	gEntityInterface->pfnSpawn(pent);
	gEntityInterface->pfnThink(pent);
	gEntityInterface->pfnTouch((*sv_player), pent);
	gEntityInterface->pfnTouch(pent, (*sv_player));
}

void CFeatureExplosion::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureExplosion::GetFeatureName()
{
	return "Create Explosion";
}