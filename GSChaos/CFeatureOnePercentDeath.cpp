#include "includes.h"

void CFeatureOnePercentDeath::Init()
{
	CChaosFeature::Init();
}

void CFeatureOnePercentDeath::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_bSpawnedRocket = false;
	m_bKillAfterDeactivate = false;

	if (ShouldKill())
	{
		edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("rpg_rocket"));
		if (!pent)
		{
			(*sv_player)->v.health = -20.0f;
			return;
		}
		pent->v.origin = (*sv_player)->v.origin;
		pent->v.angles = (*sv_player)->v.angles;
		pent->v.dmg = int((*sv_player)->v.health * 1.1);
		pent->v.dmgtime = 1.0f;
		pent->v.nextthink = gpGlobals->time + 0.1f;
		gEntityInterface->pfnSpawn(pent);
		gEntityInterface->pfnThink(pent);
		gEntityInterface->pfnTouch((*sv_player), pent);
		gEntityInterface->pfnTouch(pent, (*sv_player));

		m_bSpawnedRocket = true;
	}
}

void CFeatureOnePercentDeath::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (!m_bKillAfterDeactivate && m_bSpawnedRocket && (*sv_player)->v.health > 1.0f)
		m_bKillAfterDeactivate = true;
}

void CFeatureOnePercentDeath::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	if ((*sv_player)->v.health > 1.0f && m_bKillAfterDeactivate)
	{
		pEngfuncs->pfnClientCmd(";say \"That effect has gotten me anyway\";\n");
		(*sv_player)->v.health = -20.0f;
	}
}

const char* CFeatureOnePercentDeath::GetFeatureName()
{
	return "1% chance of death";
}

bool CFeatureOnePercentDeath::ShouldKill()
{
	return (gChaos.GetRandomValue(1, 100) == 1);
}