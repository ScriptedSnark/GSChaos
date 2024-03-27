#include "includes.h"

void CFeatureSpawnFastrun::Init()
{
	CChaosFeature::Init();
}

void CFeatureSpawnFastrun::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	fastrun = CREATE_NAMED_ENTITY(MAKE_STRING("func_wall"));

	if (!fastrun)
	{
		DeactivateFeature();
		return;
	}

	m_bSpawned = false;

	SET_MODEL(fastrun, "../chaos/fastrun.bsp");

	gEntityInterface->pfnSpawn(fastrun);

	m_flSpawnTime = gChaos.GetGlobalTime() + 3.5;
	ma_engine_play_sound(&miniAudio, "valve/sound/debris/beamstart5.wav", NULL);

	fastrun->v.origin = (*sv_player)->v.origin;
	fastrun->v.movetype = MOVETYPE_PUSH;
	fastrun->v.solid = SOLID_NOT;
}

void CFeatureSpawnFastrun::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureSpawnFastrun::OnFrame(double time)
{
	if (m_bSpawned)
		return;

	if (!fastrun || fastrun->free)
		return;

	if (gChaos.GetGlobalTime() < m_flSpawnTime)
	{
		fastrun->v.renderfx = kRenderFxFlickerFast;
		fastrun->v.rendermode = kRenderTransColor;
		fastrun->v.rendercolor = Vector(255, 0, 0);
		fastrun->v.renderamt = 64;
	}
	else
	{
		fastrun->v.renderfx = kRenderFxNone;
		fastrun->v.rendermode = kRenderNormal;
		fastrun->v.rendercolor = Vector(255, 255, 255);
		fastrun->v.renderamt = 255;
		m_bSpawned = true;
	}
}
const char* CFeatureSpawnFastrun::GetFeatureName()
{
	return "Spawn fastrun.bsp";
}