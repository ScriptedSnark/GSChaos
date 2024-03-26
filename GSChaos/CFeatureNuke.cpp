#include "includes.h"

void CFeatureNuke::Nuke()
{
	pEngfuncs->pfnClientCmd(";spk weapons/electro5.wav;spk weapons/mortarhit.wav;\n");
	//EMIT_SOUND_DYN2((*sv_player), CHAN_AUTO, "weapons/electro5.wav", 0.75, ATTN_NORM, 0, PITCH_NORM);
	//EMIT_SOUND_DYN2((*sv_player), CHAN_AUTO, "weapons/mortarhit.wav", 1.0, ATTN_NORM, 0, PITCH_NORM); // not precached

	EMIT_SOUND_DYN2((*sv_player), CHAN_WEAPON, "common/bodysplat.wav", 1, ATTN_NORM, 0, PITCH_NORM); // fake splat

	// values from crossfire.bsp
	UTIL_ScreenShake((*sv_player)->v.origin, 16.0f, 2.5f, 2.0f, 500.0f);
	UTIL_ScreenFade((*sv_player), Vector(255, 255, 255), 4.0f, 0.0f, 255, FFADE_IN);
	UTIL_TakeDamage((*sv_player)->v, 10000.0f, DMG_BLAST);
}

void CFeatureNuke::Init()
{
	CChaosFeature::Init();
}

void CFeatureNuke::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	ma_engine_play_sound(&miniAudio, "valve/sound/ambience/jetflyby1.wav", NULL);
	m_flTimeToExplode = gChaos.GetGlobalTime() + 8.0;
}

void CFeatureNuke::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureNuke::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (gChaos.GetGlobalTime() > m_flTimeToExplode)
	{
		Nuke();
		DeactivateFeature();
	}
}

const char* CFeatureNuke::GetFeatureName()
{
	return "Nuke player";
}