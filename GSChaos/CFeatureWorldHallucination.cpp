#include "includes.h"

void CFeatureWorldHallucination::ActivateFeature()
{
	CFeatureMonsterWorldspawn::ActivateFeature();

	GetWorldspawnEdict()->v.origin = Vector(0, 0, 0);
	GetWorldspawnEdict()->v.solid = SOLID_NOT;
	GetWorldspawnEdict()->v.rendermode = kRenderTransTexture;
	GetWorldspawnEdict()->v.rendercolor = Vector(32, 32, 32);
	GetWorldspawnEdict()->v.renderfx = kRenderFxPulseSlowWide;
}

void CFeatureWorldHallucination::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	edict_t* worldspawn = GetWorldspawnEdict();

	if (worldspawn && !worldspawn->free)
	{
		g_engfuncs->pfnRemoveEntity(worldspawn);
		if (worldspawn->pvPrivateData != NULL)
		{
			FREE_PRIVATE(worldspawn);
		}
	}
}

void CFeatureWorldHallucination::OnFrame(double time)
{
	if (!IsActive())
		return;

	edict_t* worldspawn = GetWorldspawnEdict();
	if (worldspawn && !worldspawn->free)
	{
		Vector currentOrigin = Vector(worldspawn->v.origin);

		Vector targetOrigin(
			gChaos.GetRandomValue(1, 125),
			gChaos.GetRandomValue(1, 125),
			gChaos.GetRandomValue(1, 125)
		);

		Vector deltaOrigin = (targetOrigin - currentOrigin) * 0.025f;

		worldspawn->v.origin = currentOrigin + deltaOrigin;
	}
}

const char* CFeatureWorldHallucination::GetFeatureName()
{
	return "World Hallucination";
}