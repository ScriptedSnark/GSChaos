#include "includes.h"

bool g_bDespawnJesus;

void CFeatureExtremeGrieferJesus::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	if (m_bActivated)
		return;

	m_flTimeForSpawn = gChaos.GetRealTime() + 38.0;
	m_bActivated = true;
	m_bSpawned = false;

	if (!m_bMusicIsPlaying) // TODO: remove this logic because SoLoud handles that already
	{
		m_bMusicIsPlaying = true;
		m_flMusicTime = gChaos.GetGlobalTime() + 192.0; // track duration (3:12)
		ChaosLoud::EmitSound(MUSIC_JESUS);
	}
}

void CFeatureExtremeGrieferJesus::OnFrame(double time)
{
	if (m_bMusicIsPlaying && gChaos.GetGlobalTime() > m_flMusicTime)
	{
		m_bMusicIsPlaying = false;
	}

	if (g_bDespawnJesus)
	{
		m_bSpawned = false;
		g_bDespawnJesus = false;
		m_flDespawnTime = 0.0;
		return;
	}

	if (m_bSpawned)
	{
		CFeatureExtremeGrieferShephard::OnFrame(time);
	}

	if (!m_bActivated)
		return;

	if (m_flTimeForSpawn > gChaos.GetRealTime())
	{
		CChaosFeature::OnFrame(time);
		return;
	}
	else
	{
		Spawn();
		m_flDespawnTime = gChaos.GetGlobalTime() + 180.0;
		m_bActivated = false;
	}
}

const char* CFeatureExtremeGrieferJesus::GetFeatureName()
{
	return "He comes back.";
}

const char* CFeatureExtremeGrieferJesus::GetModelName()
{
	return CHAOS_PATH "egj.mdl";
}

const char* CFeatureExtremeGrieferJesus::GetClassname()
{
	return "chaos_exgriefer_jesus";
}

bool CFeatureExtremeGrieferJesus::UseRenderFX()
{
	return false;
}

double CFeatureExtremeGrieferJesus::GetDuration()
{
	return 0.0;
}

bool CFeatureExtremeGrieferJesus::UseCustomDuration()
{
	return false;
}