#include "includes.h"

bool g_bDespawnExShephard = false;

void CFeatureExtremeGrieferShephard::Init()
{
	CChaosFeature::Init();
	m_flRocketTime = 0.0;
	m_bSpawned = false;
}

void CFeatureExtremeGrieferShephard::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	Spawn();
	m_flDespawnTime = gChaos.GetGlobalTime() + 180.0;
	ma_engine_play_sound(&miniAudio, "chaos/opfor01.mp3", NULL);
}

void CFeatureExtremeGrieferShephard::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureExtremeGrieferShephard::GetFeatureName()
{
	return "Spawn Extreme Griefer Shephard";
}

void CFeatureExtremeGrieferShephard::OnFrame(double time)
{
	static bool bPaused;
	bPaused = CLWrapper::GetPausedState();

	if (g_bDespawnExShephard)
	{
		m_bSpawned = false;
		g_bDespawnExShephard = false;
	}

	if (gChaos.GetGlobalTime() > m_flDespawnTime)
	{
		m_bSpawned = false;
	}

	if (bPaused)
		return;

	if (!m_bSpawned)
		return;

	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++)
	{
		e = ORIG_EDICT_NUM(i);
		if (!e)
			continue;

		edict_t* pent = e;

		if (!pent)
			continue;

		if (stricmp(STRING(pent->v.classname), "rpg_rocket"))
			continue;

		if (pent->v.owner != m_pShephard)
			continue;

		Vector vecTarget = (*sv_player)->v.origin - pent->v.origin;
		vecTarget.Normalize();

		Vector velocity = vecTarget + gpGlobals->v_forward;

		if (pent->v.velocity.Length() > 200)
		{
			pent->v.nextthink = gpGlobals->time + 1.0f;
			pent->v.waterlevel = 1; // I'm doing these hacks just for longer rocket life
			gEntityInterface->pfnThink(pent);
			pent->v.nextthink = gpGlobals->time + 1.0f;
		}

		pent->v.velocity = velocity;
		pent->v.angles = UTIL_VecToAngles(vecTarget);
	}

	if (m_pShephard)
		Think();
}

void CFeatureExtremeGrieferShephard::Spawn()
{
	if (m_pShephard && !stricmp(STRING(m_pShephard->v.classname), "chaos_exgriefer"))
	{
		g_engfuncs->pfnRemoveEntity(m_pShephard);
		if (m_pShephard->pvPrivateData != NULL)
		{
			FREE_PRIVATE(m_pShephard);
		}

		m_pShephard = NULL;
	}

	m_pShephard = CREATE_NAMED_ENTITY(MAKE_STRING("monster_generic"));

	if (!m_pShephard)
		return;

	PRECACHE_MODEL("../chaos/shephard.mdl");
	SET_MODEL(m_pShephard, "../chaos/shephard.mdl");

	gEntityInterface->pfnSpawn(m_pShephard);
	m_bSpawned = true;
	Vector playerOrigin = (*sv_player)->v.origin + gpGlobals->v_forward * 96;

	SET_SIZE(m_pShephard, (*sv_player)->v.mins, (*sv_player)->v.maxs);
	m_pShephard->v.health = 666;
	m_pShephard->v.takedamage = DAMAGE_NO;
	m_pShephard->v.origin = playerOrigin;
	m_pShephard->v.angles = (*sv_player)->v.angles;
	m_pShephard->v.movetype = MOVETYPE_STEP;
	m_pShephard->v.solid = SOLID_BBOX;
	m_pShephard->v.classname = MAKE_STRING("chaos_exgriefer");

	m_flRocketTime = gChaos.GetGlobalTime() + (SHEPHARD_ROCKET_TIME / 2.0);
}

void CFeatureExtremeGrieferShephard::Think()
{
	if (!m_pShephard)
		return;

	if (m_pShephard->free)
		return;

	if (stricmp(STRING(m_pShephard->v.classname), "chaos_exgriefer"))
		return;

	m_pShephard->v.effects = 0;
	Vector angle = (*sv_player)->v.v_angle;
	angle.y -= 180;
	m_pShephard->v.angles = angle;

	//DEBUG_PRINT("GetChaosTime(): %.01f | m_flRocketTime: %.01f\n", gChaos.GetGlobalTime(), m_flRocketTime);
	if (gChaos.GetGlobalTime() > m_flRocketTime)
	{
		DEBUG_PRINT("CFeatureExtremeGrieferShephard::LaunchRocket\n");
		LaunchRocket();
		m_flRocketTime = gChaos.GetGlobalTime() + (SHEPHARD_ROCKET_TIME / 2.0);
	}

	m_shephardLatestOrigin = m_pShephard->v.origin;
}

void CFeatureExtremeGrieferShephard::LaunchRocket()
{
	edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("rpg_rocket"));

	if (!pent)
		return;

	pent->v.origin = m_pShephard->v.origin + (m_pShephard->v.view_ofs * 64);
	pent->v.angles = m_pShephard->v.angles;
	pent->v.owner = m_pShephard;
	gEntityInterface->pfnSpawn(pent);

	EMIT_SOUND_DYN2(pent, CHAN_WEAPON, "weapons/rocketfire1.wav", 0.9, ATTN_NORM, 0, PITCH_NORM);
	EMIT_SOUND_DYN2(pent, CHAN_ITEM, "weapons/glauncher.wav", 0.7, ATTN_NORM, 0, PITCH_NORM);
}

void CFeatureExtremeGrieferShephard::Restore()
{
	if (!m_bSpawned)
		return;

	if (!m_pShephard || stricmp(STRING(m_pShephard->v.classname), "chaos_exgriefer"))
		Spawn();

	if (!stricmp(STRING(m_pShephard->v.classname), "chaos_exgriefer"))
		m_pShephard->v.origin = m_shephardLatestOrigin;
}