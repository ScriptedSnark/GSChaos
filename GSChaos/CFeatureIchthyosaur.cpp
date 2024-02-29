#include "includes.h"

void CFeatureIchthyosaur::Init()
{
	CChaosFeature::Init();
}

void CFeatureIchthyosaur::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("monster_ichthyosaur"));
	if (!pent)
		return;

	Vector origin = (*sv_player)->v.origin + (*sv_player)->v.view_ofs;
	//Vector angles = Vector(-(*sv_player)->v.v_angle.x, -(*sv_player)->v.v_angle.y, -(*sv_player)->v.v_angle.z);

	Vector angle = (*sv_player)->v.v_angle;
	angle.y -= 180;
	pent->v.origin = origin + gpGlobals->v_forward * 64;
	pent->v.angles = angle;
	pent->v.nextthink = gpGlobals->time + 0.1f;
	gEntityInterface->pfnSpawn(pent);
	gEntityInterface->pfnThink(pent);
}

void CFeatureIchthyosaur::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureIchthyosaur::GetFeatureName()
{
	return "Ichthyosaur jumpscare";
}