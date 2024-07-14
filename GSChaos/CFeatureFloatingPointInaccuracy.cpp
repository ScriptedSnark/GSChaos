#include "includes.h"

void CastFloatsToInt(Vector& vec)
{
	vec.x = (int)vec.x;
	vec.y = (int)vec.y;
	vec.z = (int)vec.z;
}

void CastFloatToInt(float& fl)
{
	fl = (int)fl;
}

void CFeatureFloatingPointInaccuracy::Init()
{
	CChaosFeature::Init();
}

void CFeatureFloatingPointInaccuracy::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_flNextThink = gChaos.GetGlobalTime() + 0.1;
}

void CFeatureFloatingPointInaccuracy::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureFloatingPointInaccuracy::PM_Move(struct playermove_s* ppmove, qboolean server)
{
	for (int i = 0; i < ppmove->numphysent; i++)
	{
		CastFloatsToInt(ppmove->physents[i].origin);
		CastFloatsToInt(ppmove->physents[i].angles);
	}

	CastFloatsToInt(ppmove->velocity);
	CastFloatsToInt(ppmove->up);
	CastFloatsToInt(ppmove->forward);
	CastFloatsToInt(ppmove->right);
	CastFloatsToInt(ppmove->punchangle);
	CastFloatToInt(ppmove->time);

	for (int i = 1; i < sv->num_edicts; i++)
	{
		edict_t* ent = ORIG_EDICT_NUM(i);
		CastFloatsToInt(ent->v.origin);
		CastFloatsToInt(ent->v.avelocity);
		CastFloatsToInt(ent->v.velocity);
		CastFloatToInt(ent->v.framerate);
		CastFloatToInt(ent->v.frame);
	}

	CastFloatsToInt(gpGlobals->v_forward);
	CastFloatsToInt(gpGlobals->v_right);
	CastFloatsToInt(gpGlobals->v_up);
	CastFloatsToInt(gpGlobals->trace_endpos);
	CastFloatsToInt(gpGlobals->trace_plane_normal);
}

void CFeatureFloatingPointInaccuracy::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (m_flNextThink > gChaos.GetGlobalTime()) // it's better to be FPS-independent
		return;

	for (int i = 1; i < sv->num_edicts; i++)
	{
		edict_t* ent = ORIG_EDICT_NUM(i);
		CastFloatsToInt(ent->v.origin);
		CastFloatsToInt(ent->v.avelocity);
		CastFloatsToInt(ent->v.velocity);
		CastFloatToInt(ent->v.framerate);
		CastFloatToInt(ent->v.frame);
	}

	CastFloatsToInt(gpGlobals->v_forward);
	CastFloatsToInt(gpGlobals->v_right);
	CastFloatsToInt(gpGlobals->v_up);
	CastFloatsToInt(gpGlobals->trace_endpos);
	CastFloatsToInt(gpGlobals->trace_plane_normal);

	m_flNextThink = gChaos.GetGlobalTime() + 0.01;

	// TODO: cast gpGlobals->time
}

const char* CFeatureFloatingPointInaccuracy::GetFeatureName()
{
	return "Floating Point Inaccuracy";
}

double CFeatureFloatingPointInaccuracy::GetDuration()
{
	return gChaos.GetChaosTime() * 0.35;
}

bool CFeatureFloatingPointInaccuracy::UseCustomDuration()
{
	return true;
}