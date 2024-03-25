#include "includes.h"

void CFeatureDeleteRandomEntity::Init()
{
	CChaosFeature::Init();
}

void CFeatureDeleteRandomEntity::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	edict_t* pEdict = ORIG_EDICT_NUM(gChaos.GetRandomValue(1, sv->num_edicts));

	if (!pEdict)
		return;

	int counter = 0;

	while (!(pEdict->v.flags & FL_MONSTER))
	{
		if (counter >= 512) // just in case
			break;

		pEdict = ORIG_EDICT_NUM(gChaos.GetRandomValue(1, sv->num_edicts));

		counter++;
	}

	if (pEdict)
	{
		g_engfuncs->pfnRemoveEntity(pEdict);

		if (pEdict->pvPrivateData != NULL)
		{
			FREE_PRIVATE(pEdict);
		}

		pEdict = NULL;
	}
}

void CFeatureDeleteRandomEntity::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureDeleteRandomEntity::GetFeatureName()
{
	return "Delete random entity :xdd:";
}