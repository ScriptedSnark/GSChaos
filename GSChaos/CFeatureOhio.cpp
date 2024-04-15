#include "includes.h"

void CFeatureOhio::Init()
{
	CChaosFeature::Init();
}

void CFeatureOhio::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_bActivated = true;
}

void CFeatureOhio::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++)
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e->v.flags & FL_WORLDBRUSH)
				continue;

			if (e->v.solid == SOLID_TRIGGER)
				continue;

			static float circle = 0.0f;
			circle += 1.0f;

			if (circle >= 360.0f)
				circle = 0.0f;

			if (!(e->v.flags & FL_CLIENT))
			{
				e->v.angles = Vector(circle, circle, circle);
				e->v.punchangle = Vector(circle / 16.f, circle / 16.f, circle / 16.f);
			}
			e->v.velocity = Vector(gChaos.GetRandomValue(-200.0f, 200.0f), gChaos.GetRandomValue(-100.0f, 450.0f), gChaos.GetRandomValue(-400.0f, 450.0f));
			e->v.fov = 180.0f;
			e->v.gravity = 0.1f;
			e->v.scale = 3.f;
			e->v.gaitsequence = e->v.sequence = 0;
			e->v.flags |= (FL_SWIM | FL_FLOAT);
			e->v.effects |= (EF_MUZZLEFLASH | EF_BRIGHTLIGHT);
			e->v.renderfx = kRenderFxExplode;
		}
	}
}

void CFeatureOhio::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++) 
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e->v.flags & FL_WORLDBRUSH)
				continue;

			if (e->v.solid == SOLID_TRIGGER)
				continue;

			if (!(e->v.flags & FL_CLIENT))
			{
				e->v.angles = Vector(0,0,0);
				e->v.punchangle = Vector(0,0,0);
			}

			e->v.velocity = Vector(0, 0, 0);
			e->v.fov = 0.0f;
			e->v.gravity = 1.0f;
			e->v.scale = 1.f;
			e->v.effects ^= (EF_MUZZLEFLASH | EF_BRIGHTLIGHT);
			e->v.renderfx = kRenderFxNone;
		}
	}
}

const char* CFeatureOhio::GetFeatureName()
{
	return "Ohio";
}

void CFeatureOhio::ResetStates()
{
	if ((*sv_player)->v.gravity <= 0.1f)
		(*sv_player)->v.gravity = 1.0f;
}