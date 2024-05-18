#include "includes.h"

void CFeatureSpawnTeleport::Init()
{
	CChaosFeature::Init();
}

void CFeatureSpawnTeleport::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	for (int i = 0; i < sv->num_edicts; i++)
	{
		edict_t* e = ORIG_EDICT_NUM(i);
		if (!e)
			continue;

		if (!stricmp(STRING(e->v.classname), "info_player_start"))
		{
			(*sv_player)->v.origin = e->v.origin;
			(*sv_player)->v.angles = e->v.angles;
			pEngfuncs->SetViewAngles(e->v.angles);
			break;
		}
	}
}

void CFeatureSpawnTeleport::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureSpawnTeleport::GetFeatureName()
{
	return "Teleport to spawn point";
}