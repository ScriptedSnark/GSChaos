#include "includes.h"

void CFeatureHook::Init()
{
	CChaosFeature::Init();
}

void CFeatureHook::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	ChaosLoud::EmitSound(SND_XBOW_HIT);
}

void CFeatureHook::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureHook::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (!(*sv_player))
		return;

	if ((*sv_player)->v.health <= 0)
		return;

	UTIL_MakeVectors((*sv_player)->v.v_angle);

	Vector end = (*sv_player)->v.origin + gpGlobals->v_forward * 8192;
	TraceResult tr;

	UTIL_TraceLine((*sv_player)->v.origin, end, dont_ignore_monsters, (*sv_player), &tr);

#ifdef COF_BUILD
	int iBeam = pEngfuncs->pEventAPI->EV_FindModelIndex("sprites/gunsmoke.spr");
#else
	int iBeam = pEngfuncs->pEventAPI->EV_FindModelIndex("sprites/smoke.spr");
#endif
	pEngfuncs->pEfxAPI->R_BeamPoints(
		(*sv_player)->v.origin,
		tr.vecEndPos,
		iBeam,
		0.05,
		2.0,
		0.1,
		255,
		0,
		0,
		0,
		0,
		255,
		0);

	Vector target = (tr.vecEndPos - (*sv_player)->v.origin).Normalize() * 666.6f;

	(*sv_player)->v.velocity = target;
}

const char* CFeatureHook::GetFeatureName()
{
	return "+hook";
}

double CFeatureHook::GetDuration()
{
	return gChaos.GetChaosTime() * 0.42;
}

bool CFeatureHook::UseCustomDuration()
{
	return true;
}