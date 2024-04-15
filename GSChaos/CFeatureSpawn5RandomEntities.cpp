#include "includes.h"

void CFeatureSpawn5RandomEntities::Init()
{
	CChaosFeature::Init();
}

void CFeatureSpawn5RandomEntities::ActivateFeature()
{
	for (int i = 0; i < 5; i++)
		CFeatureSpawnRandomEntity::ActivateFeature();
}

void CFeatureSpawn5RandomEntities::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureSpawn5RandomEntities::GetFeatureName()
{
	return "Spawn 5 random entities";
}