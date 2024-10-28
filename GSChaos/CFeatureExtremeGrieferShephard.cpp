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

	m_bSpawned = false;

	Spawn();
	m_flDespawnTime = gChaos.GetGlobalTime() + 180.0;

	ChaosLoud::EmitSound(MUSIC_OPFOR01);
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
		m_flDespawnTime = 0.0;
		return;
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
	if (m_pShephard && !stricmp(STRING(m_pShephard->v.classname), GetClassname()))
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

	PRECACHE_MODEL(const_cast<char*>(GetModelName()));
	SET_MODEL(m_pShephard, const_cast<char*>(GetModelName()));

	gEntityInterface->pfnSpawn(m_pShephard);
	m_bSpawned = true;
	Vector playerOrigin = (*sv_player)->v.origin;
	playerOrigin.z += 32.f;

	SET_SIZE(m_pShephard, (*sv_player)->v.mins, (*sv_player)->v.maxs);
	m_pShephard->v.health = 777;
	m_pShephard->v.takedamage = DAMAGE_NO;
	m_pShephard->v.origin = playerOrigin;
	m_pShephard->v.angles = (*sv_player)->v.angles;
	m_pShephard->v.movetype = MOVETYPE_NOCLIP;
	m_pShephard->v.solid = SOLID_NOT;
	m_pShephard->v.classname = MAKE_STRING(GetClassname());

	m_flRocketTime = gChaos.GetGlobalTime() + (SHEPHARD_ROCKET_TIME / 2.0);
}

void CFeatureExtremeGrieferShephard::Think()
{
	if (!m_pShephard)
		return;

	if (m_pShephard->free)
		return;

	if (stricmp(STRING(m_pShephard->v.classname), GetClassname()))
		return;

	m_pShephard->v.effects = 0;
	Vector angle = (*sv_player)->v.v_angle;
	angle.y -= 180;
	m_pShephard->v.angles = angle;

	if (UseRenderFX())
	{
		m_pShephard->v.rendercolor = Vector(255, 0, 0);
		m_pShephard->v.renderamt = 255;
		m_pShephard->v.renderfx = kRenderFxGlowShell;
	}
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

	if (!pent || RANDOM_LONG(1, 100) <= 5)
	{
		Vector target = (*sv_player)->v.origin - m_pShephard->v.origin;

		float distance = Length(target);
		Vector direction = target / distance;
		Vector velocity = direction * gChaos.GetRandomValue(777.0f, MAGNET_SPEED);

		m_pShephard->v.velocity = velocity;
		m_pShephard->v.movetype = MOVETYPE_NOCLIP;
		m_pShephard->v.solid = SOLID_BBOX;
		m_pShephard->v.gaitsequence = m_pShephard->v.sequence = 10; // swim
		Vector angle = (*sv_player)->v.v_angle;
		angle.y -= 180;
		m_pShephard->v.angles = angle;

		if (abs(distance) < gChaos.GetRandomValue(100.0f, 300.0f))
		{
			m_pShephard->v.sequence = m_pShephard->v.gaitsequence = 26; // crowbar
			pEngfuncs->pfnClientCmd(";spk weapons/cbar_hitbod3;\n");
			UTIL_TakeDamage((*sv_player)->v, gChaos.GetRandomValue(5.0f, 15.0f), DMG_SLASH);
			(*sv_player)->v.punchangle = Vector(gChaos.GetRandomValue(-64.0f, 64.f), gChaos.GetRandomValue(-84.0f, 0.0f), 0.0f);
		}
		return;
	}

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

	if (!m_pShephard || stricmp(STRING(m_pShephard->v.classname), GetClassname()))
		Spawn();

	if (!stricmp(STRING(m_pShephard->v.classname), GetClassname()))
		m_pShephard->v.origin = m_shephardLatestOrigin;
}

const char* CFeatureExtremeGrieferShephard::GetModelName()
{
	return CHAOS_PATH "shephard.mdl";
}

const char* CFeatureExtremeGrieferShephard::GetClassname()
{
	return "chaos_exgriefer";
}

bool CFeatureExtremeGrieferShephard::UseRenderFX()
{
	return true;
}

double CFeatureExtremeGrieferShephard::GetDuration()
{
	return 180.0;
}

bool CFeatureExtremeGrieferShephard::UseCustomDuration()
{
	return true;
}