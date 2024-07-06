#include "includes.h"

void CFeatureDelete5RandomEntities::Init()
{
	CChaosFeature::Init();
}

void CFeatureDelete5RandomEntities::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	for (int i = 0; i < 5; i++)
	{
		edict_t* pEdict = ORIG_EDICT_NUM(gChaos.GetRandomValue(1, sv->num_edicts));

		if (!pEdict)
			continue;

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
}

void CFeatureDelete5RandomEntities::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureDelete5RandomEntities::GetFeatureName()
{
	return "Delete 5 random entities";
}