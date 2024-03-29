#include "includes.h"

void CFeatureOnePercentDeath::Init()
{
	CChaosFeature::Init();
}

void CFeatureOnePercentDeath::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	if (gChaos.GetRandomValue(1, 100) == 1)
	{
		edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("rpg_rocket"));
		if (!pent)
		{
			(*sv_player)->v.health = -20.0f;
			return;
		}
		pent->v.origin = (*sv_player)->v.origin;
		pent->v.angles = (*sv_player)->v.angles;
		pent->v.dmg = 2048;
		pent->v.dmgtime = 1.0f;
		pent->v.nextthink = gpGlobals->time + 0.1f;
		gEntityInterface->pfnSpawn(pent);
		gEntityInterface->pfnThink(pent);
		gEntityInterface->pfnTouch((*sv_player), pent);
		gEntityInterface->pfnTouch(pent, (*sv_player));

		if ((*sv_player)->v.health > 1.0f)
			(*sv_player)->v.health = -20.0f;
	}
}

void CFeatureOnePercentDeath::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureOnePercentDeath::GetFeatureName()
{
	return "1% chance of death";
}