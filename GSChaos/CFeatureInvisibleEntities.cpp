#include "includes.h"

_EDICT_NUM ORIG_EDICT_NUM = NULL;

void CFeatureInvisibleEntities::Init()
{
	CChaosFeature::Init();

	utils.FindAsync(ORIG_EDICT_NUM, patterns::engine::EDICT_NUM);
}

void CFeatureInvisibleEntities::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_bActivated = true;
}

void CFeatureInvisibleEntities::OnFrame(double time)
{
	if (!m_bActivated)
		return;
	
	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++)
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e->v.flags & FL_CLIENT || !(e->v.flags & FL_MONSTER))
				continue;

			e->v.rendermode = kRenderTransTexture;
			e->v.renderamt = 20;
		}
	}
}

void CFeatureInvisibleEntities::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++)
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e->v.flags & FL_CLIENT || !(e->v.flags & FL_MONSTER))
				continue;

			e->v.rendermode = kRenderNormal;
			e->v.renderamt = 255;
		}
	}

	m_bActivated = false;
}

const char* CFeatureInvisibleEntities::GetFeatureName()
{
	return "Invisible entities";
}