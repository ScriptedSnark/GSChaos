#include "includes.h"

void CFeatureShuffleEntitiesPositions::Init()
{
	CChaosFeature::Init();
}

void CFeatureShuffleEntitiesPositions::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	static std::random_device randDev;
	std::mt19937 randMT(randDev());

	std::vector<Vector> entPositions;
	std::vector<int> entNumbers;

	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++)
	{
		e = ORIG_EDICT_NUM(i);
		if (e)
		{
			if (e->v.flags & FL_CLIENT)
				continue;

			if (e->v.solid == SOLID_TRIGGER)
				continue;

			if (strstr(STRING(e->v.classname), "trigger_") || strstr(STRING(e->v.classname), "info_"))
				continue;

			entPositions.push_back(e->v.origin);
			entNumbers.push_back(i);
		}
	}

	std::shuffle(entPositions.begin(), entPositions.end(), randMT);

	for (size_t i = 0; i < entPositions.size(); i++)
	{
		e = ORIG_EDICT_NUM(entNumbers[i]);
		if (e)
		{
			if (e->v.flags & FL_CLIENT)
				continue;

			if (e->v.solid == SOLID_TRIGGER)
				continue;

			if (strstr(STRING(e->v.classname), "trigger_") || strstr(STRING(e->v.classname), "info_"))
				continue;

			e->v.origin = entPositions[i];
		}
	}

	SERVER_COMMAND(";save chaos;load chaos;\n");
}

void CFeatureShuffleEntitiesPositions::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureShuffleEntitiesPositions::GetFeatureName()
{
	return "Shuffle entities positions";
}