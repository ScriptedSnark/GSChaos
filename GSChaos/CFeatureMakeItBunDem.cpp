#include "includes.h"

int g_flameSpr;

void CFeatureMakeItBunDem::Burn()
{
	int damage = gChaos.GetRandomValue(1, 5);
	UTIL_TakeDamage((*sv_player)->v, (float)damage, DMG_BURN);
}

void CFeatureMakeItBunDem::Init()
{
	CChaosFeature::Init();
}

void CFeatureMakeItBunDem::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;

	if (chaos_dmca_safe->value == 0)
	{
		ma_engine_set_volume(&miniAudio, CVAR_GET_FLOAT("volume"));
		ma_engine_play_sound(&miniAudio, "chaos/ucieczka_nastroj.wav", NULL);
	}
	
	sfx_t* sfx = S_LateLoadSound("../../chaos/burn.wav");
	int viewentity = g_bHL25 ? cl_hl25->viewentity : cl->viewentity;
	ORIG_S_StartStaticSound(viewentity, CHAN_AUTO, sfx, (*sv_player)->v.origin, VOL_NORM, 1.0, 0, PITCH_NORM); // dunno how to stop without hacks like "stopsound"
}

void CFeatureMakeItBunDem::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;
}

void CFeatureMakeItBunDem::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	static double burnTimer = gChaos.GetGlobalTime() + 0.6;
	static double flameTimer = gChaos.GetGlobalTime() + 0.1;

	if (gChaos.GetGlobalTime() > burnTimer)
	{
		g_flameSpr = PRECACHE_MODEL("../chaos/flame.spr"); // smh
		Burn();
		burnTimer = gChaos.GetGlobalTime() + 0.6;
	}

	if (gChaos.GetGlobalTime() > flameTimer)
	{
		MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);
		WRITE_BYTE(TE_SPRITE); // TE id
		WRITE_COORD((*sv_player)->v.origin[0] + gChaos.GetRandomValue(-5, 5));// x
		WRITE_COORD((*sv_player)->v.origin[1] + gChaos.GetRandomValue(-5, 5));// y
		WRITE_COORD((*sv_player)->v.origin[2] + gChaos.GetRandomValue(-10, 10)); // z
		WRITE_SHORT(g_flameSpr); // sprite
		WRITE_BYTE(gChaos.GetRandomValue(5, 10)); // scale
		WRITE_BYTE(200); // brightness
		WRITE_BYTE(1);
		MESSAGE_END();

		flameTimer = gChaos.GetGlobalTime() + 0.1;
	}
}

const char* CFeatureMakeItBunDem::GetFeatureName()
{
	return "Make It Bun Dem";
}