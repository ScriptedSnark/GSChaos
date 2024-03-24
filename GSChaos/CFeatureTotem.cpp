#include "includes.h"

void CFeatureTotem::Init()
{
	CChaosFeature::Init();
}

void CFeatureTotem::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_bActivated = true;
	m_flTotemTime = gChaos.GetGlobalTime() + TOTEM_TIME;
	
	ma_engine_play_sound(&miniAudio, "chaos/totem.wav", NULL);
}

void CFeatureTotem::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (m_flTotemTime > gChaos.GetGlobalTime())
	{
		(*sv_player)->v.health += 0.15f;
		(*sv_player)->v.armorvalue += 0.02f;
		(*sv_player)->v.flags |= FL_GODMODE;
		Vector origin = (*sv_player)->v.origin;
		origin.z += 20.f;

		PARTICLE_EFFECT(origin, Vector(0, 0, 0), gChaos.GetRandomValue(250, 255), gChaos.GetRandomValue(10, 50));
	}
	else
		DeactivateFeature();
}

void CFeatureTotem::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	(*sv_player)->v.flags &= ~FL_GODMODE;
	m_bActivated = false;
}

const char* CFeatureTotem::GetFeatureName()
{
	return "Totem of Undying";
}