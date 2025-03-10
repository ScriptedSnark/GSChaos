#include "includes.h"

bool g_bDespawnJesus;

void CFeatureExtremeGrieferJesus::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	if (m_bActivated)
		return;

	m_flTimeForSpawn = pEngfuncs->GetAbsoluteTime() + 38.0;
	m_bActivated = true;
	m_bSpawned = false;

	ChaosLoud::EmitSound(MUSIC_JESUS);
}

void CFeatureExtremeGrieferJesus::OnFrame(double time)
{
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

	if (m_flTimeForSpawn > pEngfuncs->GetAbsoluteTime())
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