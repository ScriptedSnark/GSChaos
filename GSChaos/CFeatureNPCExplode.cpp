#include "includes.h"

void CFeatureNPCExplode::Init()
{
	CChaosFeature::Init();
}

void CFeatureNPCExplode::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_iExplosionCount = 0;

	// rip edict limit
	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++)
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e->v.flags & FL_CLIENT || !(e->v.flags & FL_MONSTER))
				continue;

			// It won't fix potential crash but I don't care :DDDD
			if (sv->num_edicts >= (sv->max_edicts - 100) || m_iExplosionCount > 30) // idk why 100
			{
				e->v.health = -69;
				e->v.deadflag = DEAD_DEAD;
				continue;
			}

			edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("rpg_rocket"));
			if (!pent)
				return;

			m_iExplosionCount++;
			pent->v.origin = e->v.origin;
			pent->v.angles = e->v.angles;
			pent->v.dmg = 200;
			pent->v.dmgtime = 1.0f;
			pent->v.nextthink = gpGlobals->time + 0.1f;
			gEntityInterface->pfnSpawn(pent);
			gEntityInterface->pfnThink(pent);
			gEntityInterface->pfnTouch(e, pent);
			gEntityInterface->pfnTouch(pent, e);
		}
	}
}

void CFeatureNPCExplode::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureNPCExplode::GetFeatureName()
{
	return "Every NPC explodes";
}