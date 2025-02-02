#include "includes.h"

void CFeatureMovetypeBounce::Init()
{
	CChaosFeature::Init();
}

void CFeatureMovetypeBounce::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureMovetypeBounce::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureMovetypeBounce::OnFrame(double time)
{
	if (!IsActive())
		return;
	
	for (int i = 1; i < sv->num_edicts; i++)
	{
		edict_t* ent = ORIG_EDICT_NUM(i);

		if (ent->v.solid == SOLID_TRIGGER)
			continue;

		if (strstr(STRING(ent->v.classname), "trigger_") || strstr(STRING(ent->v.classname), "info_") || strstr(STRING(ent->v.classname), "env_"))
			continue;

		if (ent->v.model == 0)
			continue;

		if (ent->v.flags & FL_DORMANT)
			continue;

		ent->v.movetype = MOVETYPE_BOUNCE;
		ent->v.solid = SOLID_SLIDEBOX;
	}	
}

const char* CFeatureMovetypeBounce::GetFeatureName()
{
	return "MOVETYPE_BOUNCE + SOLID_SLIDEBOX";
}

double CFeatureMovetypeBounce::GetDuration()
{
	return gChaos.GetChaosTime() * 0.75;
}

bool CFeatureMovetypeBounce::UseCustomDuration()
{
	return true;
}

bool CFeatureMovetypeBounce::CanBeInfinite()
{
	return true;
}