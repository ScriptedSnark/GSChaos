#include "includes.h"

// I can change the behavior of this effect but meh...

void CFeatureLobotomy::Init()
{
	CChaosFeature::Init();
}

void CFeatureLobotomy::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;
	m_flLobotomyTPTime = gChaos.GetGlobalTime() + LOBOTOMY_TP_TIME;
	m_lobotomyOrigin = (*sv_player)->v.origin;

	if ((*sv_player)->v.flags & FL_DUCKING)
		m_lobotomyOrigin.z += 16.0f; // not good

	m_lobotomyAngles = (*sv_player)->v.v_angle;
	m_lobotomyVelocity = (*sv_player)->v.velocity;
	pEngfuncs->GetViewAngles(m_lobotomyViewAngles);
}

void CFeatureLobotomy::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;
	m_bPlayedSound = false;
}

void CFeatureLobotomy::DoMegaLobotomy(double time)
{
	if (m_flLobotomyTPTime >= gChaos.GetGlobalTime())
		return;

	UTIL_ScreenFade((*sv_player), Vector(gChaos.GetRandomValue(0, 200), gChaos.GetRandomValue(0, 160), 0), 1.35f, 0.1f, 100, FFADE_IN);
	(*sv_player)->v.origin = m_lobotomyOrigin;
	(*sv_player)->v.v_angle = m_lobotomyAngles;

	pEngfuncs->SetViewAngles(m_lobotomyViewAngles);

	if (gChaos.GetRandomValue(1, 2) == 1)
		(*sv_player)->v.velocity = m_lobotomyVelocity;
	else
		(*sv_player)->v.velocity = -m_lobotomyVelocity;

	(*sv_player)->v.health = (int)gChaos.GetRandomValue(2, 100);
	(*sv_player)->v.armorvalue = (int)gChaos.GetRandomValue(2, 100);

	EMIT_SOUND_DYN2((*sv_player), CHAN_ITEM, "fvox/beep.wav", 1.0, ATTN_IDLE, 0, gChaos.GetRandomValue(PITCH_LOW - 20, PITCH_HIGH + 20));

	m_flLobotomyTPTime = gChaos.GetGlobalTime() + (((CHAOS_ACTIVATE_TIMER / 2.0) / time) / 2.0); // :skull:
}

void CFeatureLobotomy::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (time > (CHAOS_ACTIVATE_TIMER - 10.0f))
	{
		if (!m_bPlayedSound)
		{
			ma_engine_play_sound(&miniAudio, "chaos/lobotomy.wav", NULL);
			m_bPlayedSound = true;
		}

		DoMegaLobotomy(time);
		return;
	}

	if (m_flLobotomyTPTime <= gChaos.GetGlobalTime())
	{
		UTIL_ScreenFade((*sv_player), Vector(gChaos.GetRandomValue(0, 200), gChaos.GetRandomValue(0, 160), 0), 1.35f, 0.1f, 255, FFADE_IN);
		(*sv_player)->v.origin = m_lobotomyOrigin;
		(*sv_player)->v.v_angle = m_lobotomyAngles;

		pEngfuncs->SetViewAngles(m_lobotomyViewAngles);

		(*sv_player)->v.velocity = m_lobotomyVelocity;

		EMIT_SOUND_DYN2((*sv_player), CHAN_ITEM, "fvox/beep.wav", 1.0, ATTN_IDLE, 0, gChaos.GetRandomValue(PITCH_LOW - 20, PITCH_HIGH + 20));
		
		if (time > (CHAOS_ACTIVATE_TIMER - 10.0f))
			m_flLobotomyTPTime = gChaos.GetGlobalTime() + 0.5;
		else
			m_flLobotomyTPTime = gChaos.GetGlobalTime() + (LOBOTOMY_TP_TIME / 4.0);
	}
}

const char* CFeatureLobotomy::GetFeatureName()
{
	return "Lobotomy";
}