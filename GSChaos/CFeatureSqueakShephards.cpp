#include "includes.h"

void CFeatureSqueakShephards::Init()
{
	CChaosFeature::Init();
}

void CFeatureSqueakShephards::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	// spawn squeaks
	edict_t* pent;
	for (int i = 0; i <= 5; i++)
	{
		pent = SpawnSqueak();

		if (!pent)
			continue;

		Vector origin = (*sv_player)->v.origin + (*sv_player)->v.view_ofs;
		Vector angle = (*sv_player)->v.v_angle;

		if (i != 0)
			pent->v.origin = origin + gpGlobals->v_forward * (96 * i);
		else
			pent->v.origin = origin + gpGlobals->v_forward * 64;

		pent->v.angles = angle;

		pent->v.effects = 0;
	}
}

void CFeatureSqueakShephards::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureSqueakShephards::GetFeatureName()
{
	return "Squeak Shephard Ambush";
}