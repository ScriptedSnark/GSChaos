#include "includes.h"

void CFeatureOverthinking::Init()
{
	CChaosFeature::Init();
}

void CFeatureOverthinking::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureOverthinking::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureOverthinking::OnFrame(double time)
{
	if (!IsActive())
		return;
	
	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++)
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e->v.flags & FL_CLIENT)
				continue;

			e->v.nextthink = gpGlobals->time + 0.01f;
		}
	}
}

const char* CFeatureOverthinking::GetFeatureName()
{
	return "Overthinking";
}

double CFeatureOverthinking::GetDuration()
{
	return gChaos.GetChaosTime() * 0.2;
}

bool CFeatureOverthinking::UseCustomDuration()
{
	return true;
}

bool CFeatureOverthinking::CanBeInfinite()
{
	return true;
}