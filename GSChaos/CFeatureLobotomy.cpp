#include "includes.h"

// I can change the behavior of this effect but meh...

void CFeatureLobotomy::Init()
{
	CChaosFeature::Init();
}

void CFeatureLobotomy::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_flLobotomyTPTime = gChaos.GetGlobalTime() + LOBOTOMY_TP_TIME;
	m_lobotomyOrigin[0] = (*sv_player)->v.origin;

	if ((*sv_player)->v.flags & FL_DUCKING)
		m_lobotomyOrigin[0].z += 16.0f; // not good

	m_lobotomyAngles[0] = (*sv_player)->v.v_angle;
	m_lobotomyVelocity[0] = (*sv_player)->v.velocity;
	pEngfuncs->GetViewAngles(m_lobotomyViewAngles[0]);
}

void CFeatureLobotomy::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bPlayedSound = false;
	m_bInitializedSecondPos = false;
}

void CFeatureLobotomy::DoMegaLobotomy(double time)
{
	if (m_flLobotomyTPTime > gChaos.GetGlobalTime())
		return;

	int pos = gChaos.GetRandomValue(0, 1);

	if (!m_bInitializedSecondPos)
		pos = 0;

	UTIL_ScreenFade((*sv_player), Vector(gChaos.GetRandomValue(0, 200), gChaos.GetRandomValue(0, 160), 0), 1.35f, 0.1f, 100, FFADE_IN);
	(*sv_player)->v.origin = m_lobotomyOrigin[pos];
	(*sv_player)->v.v_angle = m_lobotomyAngles[pos];

	pEngfuncs->SetViewAngles(m_lobotomyViewAngles[pos]);

	if (gChaos.GetRandomValue(1, 2) == 1)
		(*sv_player)->v.velocity = m_lobotomyVelocity[pos];
	else
		(*sv_player)->v.velocity = -m_lobotomyVelocity[pos];

	(*sv_player)->v.health = (int)gChaos.GetRandomValue(2, 100);
	(*sv_player)->v.armorvalue = (int)gChaos.GetRandomValue(2, 100);

	EMIT_SOUND_DYN2((*sv_player), CHAN_ITEM, "fvox/beep.wav", 1.0, ATTN_IDLE, 0, gChaos.GetRandomValue(PITCH_LOW - 20, PITCH_HIGH + 20));

	m_flLobotomyTPTime = gChaos.GetGlobalTime() + (((GetDuration() / 2.0) / time) / 2.0); // :skull:
}

void CFeatureLobotomy::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (time > (GetDuration() - 10.0f))
	{
		if (!m_bPlayedSound)
		{
			ChaosLoud::EmitSound(SND_LOBOTOMY);
			m_bPlayedSound = true;
		}

		DoMegaLobotomy(time);
		return;
	}

	if (m_flLobotomyTPTime < gChaos.GetGlobalTime())
	{
		if (!m_bInitializedSecondPos)
		{
			m_lobotomyOrigin[1] = (*sv_player)->v.origin;

			if ((*sv_player)->v.flags & FL_DUCKING)
				m_lobotomyOrigin[1].z += 16.0f; // not good

			m_lobotomyAngles[1] = (*sv_player)->v.v_angle;
			m_lobotomyVelocity[1] = (*sv_player)->v.velocity;
			pEngfuncs->GetViewAngles(m_lobotomyViewAngles[1]);

			m_bInitializedSecondPos = true;
		}

		UTIL_ScreenFade((*sv_player), Vector(gChaos.GetRandomValue(0, 200), gChaos.GetRandomValue(0, 160), 0), 1.35f, 0.1f, 255, FFADE_IN);
		(*sv_player)->v.origin = m_lobotomyOrigin[0];
		(*sv_player)->v.v_angle = m_lobotomyAngles[0];

		pEngfuncs->SetViewAngles(m_lobotomyViewAngles[0]);

		(*sv_player)->v.velocity = m_lobotomyVelocity[0];

		EMIT_SOUND_DYN2((*sv_player), CHAN_ITEM, "fvox/beep.wav", 1.0, ATTN_IDLE, 0, gChaos.GetRandomValue(PITCH_LOW - 20, PITCH_HIGH + 20));
		
		if (time > (GetDuration() - 10.0f))
			m_flLobotomyTPTime = gChaos.GetGlobalTime() + 0.5;
		else
			m_flLobotomyTPTime = gChaos.GetGlobalTime() + (LOBOTOMY_TP_TIME / 4.0);
	}
}

const char* CFeatureLobotomy::GetFeatureName()
{
	return "Lobotomy";
}