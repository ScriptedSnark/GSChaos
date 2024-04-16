#include "includes.h"

void CFeatureGlobalGodMode::Init()
{
	CChaosFeature::Init();
}

void CFeatureGlobalGodMode::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_bActivated = true;

	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++) 
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e == (*sv_player))
			{
				e->v.flags |= FL_GODMODE;
				continue;
			}

			if (e->v.flags & FL_WORLDBRUSH)
				continue;

			if (e->v.solid == SOLID_TRIGGER)
				continue;

			if (e->v.flags & FL_MONSTER)
			{
				e->v.takedamage = DAMAGE_NO;
			}
		}
	}
}

void CFeatureGlobalGodMode::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	m_bActivated = false;

	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++) 
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e == (*sv_player))
			{
				e->v.flags &= ~FL_GODMODE;
				continue;
			}

			if (e->v.flags & FL_WORLDBRUSH)
				continue;

			if (e->v.solid == SOLID_TRIGGER)
				continue;

			if (e->v.flags & FL_MONSTER)
			{
				e->v.takedamage = DAMAGE_YES;
			}
		}
	}
}

void CFeatureGlobalGodMode::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++) 
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e == (*sv_player))
			{
				e->v.flags |= FL_GODMODE;
				continue;
			}

			if (e->v.flags & FL_WORLDBRUSH)
				continue;

			if (e->v.solid == SOLID_TRIGGER)
				continue;

			if (e->v.flags & FL_MONSTER)
			{
				e->v.takedamage = DAMAGE_NO;
			}
		}
	}
}

const char* CFeatureGlobalGodMode::GetFeatureName()
{
	return "Everyone has God Mode!";
}

double CFeatureGlobalGodMode::GetDuration()
{
	return gChaos.GetChaosTime() * 0.48;
}

bool CFeatureGlobalGodMode::UseCustomDuration()
{
	return true;
}