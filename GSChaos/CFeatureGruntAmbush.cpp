#include "includes.h"

void CFeatureGruntAmbush::Init()
{
	CChaosFeature::Init();
}

void CFeatureGruntAmbush::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	// spawn grunts
	for (int i = 0; i <= 5; i++)
	{
		edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("monster_human_grunt"));
		if (!pent)
			continue;

		Vector origin = (*sv_player)->v.origin + (*sv_player)->v.view_ofs;
		//Vector angles = Vector(-(*sv_player)->v.v_angle.x, -(*sv_player)->v.v_angle.y, -(*sv_player)->v.v_angle.z);

		Vector angle = (*sv_player)->v.v_angle;
		//angle.y -= 180;

		if (i != 0)
			pent->v.origin = origin + gpGlobals->v_forward * (96 * i);
		else
			pent->v.origin = origin + gpGlobals->v_forward * 64;

		pent->v.angles = angle;

		//pent->v.origin = (*sv_player)->v.origin + Vector(8 * i, 0, 0);
		//pent->v.angles = (*sv_player)->v.angles;
		gEntityInterface->pfnSpawn(pent);

		pent->v.effects = 0;
	}
}

void CFeatureGruntAmbush::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureGruntAmbush::GetFeatureName()
{
	return "Human grunt ambush!";
}