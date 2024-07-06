#include "includes.h"

void CFeatureDinnerbone::Init()
{
	CChaosFeature::Init();
}

void CFeatureDinnerbone::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureDinnerbone::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureDinnerbone::HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	if (ent->model->type != mod_studio)
		return;

	ent->angles.z = 180;
	ent->curstate.angles.z = 180;

	if (type != 1) // ET_PLAYER
	{
		ent->curstate.origin.z += (ent->curstate.maxs.z - ent->curstate.mins.z);
		ent->origin = ent->curstate.origin;
	}

	// special logic for ducking (TODO: fix for human grunts)
	if (ent->curstate.usehull == 1)
	{
		ent->curstate.origin.z += 18.0f;
		ent->origin = ent->curstate.origin;
	}
}

const char* CFeatureDinnerbone::GetFeatureName()
{
	return "Dinnerbone";
}

double CFeatureDinnerbone::GetDuration()
{
	return gChaos.GetChaosTime() * 1.1;
}

bool CFeatureDinnerbone::UseCustomDuration()
{
	return true;
}