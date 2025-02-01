#include "includes.h"

const int FIREWORKS_MAXLIFE = 10;
const int FIREWORKS_MINLIFE = 5;
const float FIREWORKS_VELOCITY_MIN = 1000.0f;
const float FIREWORKS_VELOCITY_MAX = 1400.0f;
const float FIREWORKS_VELOCITY_XY = 100.0f;
const int FIREWORKS_COLORTYPE = 1;

void CFeatureFirework::Init()
{
	CChaosFeature::Init();
	m_flNextFireworkTime = 0.0f;
	m_flNextShooterTime = 0.0f;
	m_vFireworks.clear();
}

void CFeatureFirework::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_iSprSmoke = PRECACHE_MODEL("sprites/smoke.spr");
	m_iSprFlare6 = PRECACHE_MODEL("sprites/flare6.spr");
	m_iSprLgtning = PRECACHE_MODEL("sprites/lgtning.spr");

	PRECACHE_SOUND("../../chaos/firework.wav");
	PRECACHE_SOUND("../../chaos/firework_launch.wav");

	m_flNextFireworkTime = gpGlobals->time + 0.1f;
	m_flNextShooterTime = gpGlobals->time + 0.3f;
}

void CFeatureFirework::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	for (edict_t* pEdict : m_vFireworks)
	{
		if (!FNullEnt(pEdict))
		{
			REMOVE_ENTITY(pEdict);
		}
	}

	m_vFireworks.clear();
}

void CFeatureFirework::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (!(*sv_player) || sv->state != ss_active)
		return;

	if (gpGlobals->time >= m_flNextFireworkTime)
	{
		FireworksThink();
		m_flNextFireworkTime = gpGlobals->time + 0.1f;
	}

	if (gpGlobals->time >= m_flNextShooterTime)
	{
		ShooterThink();
		m_flNextShooterTime = gpGlobals->time + 0.5f;
	}
}

const char* CFeatureFirework::GetFeatureName()
{
	return "Fireworks";
}

double CFeatureFirework::GetDuration()
{
	return gChaos.GetChaosTime() * 0.47;
}

bool CFeatureFirework::UseCustomDuration()
{
	return true;
}

bool CFeatureFirework::CanBeInfinite()
{
	return false;
}

void CFeatureFirework::Restore()
{
	if (!IsActive())
		return;

	m_iSprSmoke = PRECACHE_MODEL("sprites/smoke.spr");
	m_iSprFlare6 = PRECACHE_MODEL("sprites/flare6.spr");
	m_iSprLgtning = PRECACHE_MODEL("sprites/lgtning.spr");

	PRECACHE_SOUND("../../chaos/firework.wav");
	PRECACHE_SOUND("../../chaos/firework_launch.wav");

	m_flNextFireworkTime = gpGlobals->time + 0.1f;
	m_flNextShooterTime = gpGlobals->time + 0.3f;

	m_vFireworks.clear();
}

void CFeatureFirework::FireworksThink()
{
	for (auto it = m_vFireworks.begin(); it != m_vFireworks.end();)
	{
		edict_t* pEdict = *it;
		if (FNullEnt(pEdict) || pEdict->free || strcmp(STRING(pEdict->v.classname), "chaos_fireworks"))
		{
			it = m_vFireworks.erase(it);
			continue;
		}

		Vector velocity = pEdict->v.velocity;
		velocity.x = RANDOM_FLOAT(-FIREWORKS_VELOCITY_XY, FIREWORKS_VELOCITY_XY);
		velocity.y = RANDOM_FLOAT(-FIREWORKS_VELOCITY_XY, FIREWORKS_VELOCITY_XY);
		velocity.z = RANDOM_FLOAT(FIREWORKS_VELOCITY_MIN, FIREWORKS_VELOCITY_MAX);
		pEdict->v.velocity = velocity;

		if (pEdict->v.iuser1 <= 0)
		{
			Explode(pEdict);
			it = m_vFireworks.erase(it);
		}
		else
		{
			pEdict->v.iuser1--;
			++it;
		}
	}
}

void CFeatureFirework::ShooterThink()
{
	Vector origin = (*sv_player)->v.origin;
	Vector angles = Vector(90.0f, RANDOM_FLOAT(0.0f, 360.0f), 0.0f);

	int r = 255, g = 255, b = 255;
	if (FIREWORKS_COLORTYPE)
	{
		switch (RANDOM_LONG(0, 6))
		{
		case 0: r = 255; g = 0; b = 0; break;
		case 1: r = 0; g = 255; b = 0; break;
		case 2: r = 0; g = 0; b = 255; break;
		case 3: r = 0; g = 255; b = 255; break;
		case 4: r = 255; g = 0; b = 255; break;
		case 5: r = 255; g = 255; b = 0; break;
		case 6: r = 255; g = 128; b = 0; break;
		}
	}
	else
	{
		r = RANDOM_LONG(0, 255);
		g = RANDOM_LONG(0, 255);
		b = RANDOM_LONG(0, 255);
	}

	CreateFirework(origin, angles, r, g, b);
}

void CFeatureFirework::Explode(edict_t* pEdict)
{
	Vector origin = pEdict->v.origin;
	int r = pEdict->v.iuser2;
	int g = pEdict->v.iuser3;
	int b = pEdict->v.iuser4;

	STOP_SOUND(pEdict, CHAN_BODY, "weapons/rocket1.wav");

	MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
	WRITE_BYTE(TE_BEAMDISK);
	WRITE_COORD(origin.x);
	WRITE_COORD(origin.y);
	WRITE_COORD(origin.z);
	WRITE_COORD(origin.x);
	WRITE_COORD(origin.y);
	WRITE_COORD(origin.z + RANDOM_FLOAT(250.0f, 750.0f));
	WRITE_SHORT(RANDOM_LONG(0, 1) ? m_iSprFlare6 : m_iSprLgtning);
	WRITE_BYTE(0);
	WRITE_BYTE(0);
	WRITE_BYTE(45);
	WRITE_BYTE(150);
	WRITE_BYTE(0);
	WRITE_BYTE(r);
	WRITE_BYTE(g);
	WRITE_BYTE(b);
	WRITE_BYTE(255);
	WRITE_BYTE(0);
	MESSAGE_END();

	EMIT_SOUND_DYN2(pEdict, CHAN_WEAPON, "../../chaos/firework.wav", 1.0, ATTN_NORM, 0, 100);

	pEdict->v.flags |= FL_KILLME;
}

void CFeatureFirework::CreateFirework(Vector origin, Vector angles, int r, int g, int b)
{
	// in case if it's not precached for some reason
	PRECACHE_SOUND("../../chaos/firework.wav");
	PRECACHE_SOUND("../../chaos/firework_launch.wav");

	edict_t* pEdict = CREATE_NAMED_ENTITY(MAKE_STRING("monster_furniture"));
	if (!FNullEnt(pEdict))
	{
		SET_ORIGIN(pEdict, origin);
		pEdict->v.angles = angles;
		pEdict->v.classname = MAKE_STRING("chaos_fireworks");
		pEdict->v.movetype = MOVETYPE_FLY;
		pEdict->v.solid = SOLID_NOT;
		pEdict->v.velocity = Vector(RANDOM_FLOAT(-150.0f, 150.0f), RANDOM_FLOAT(-150.0f, 150.0f), RANDOM_FLOAT(FIREWORKS_VELOCITY_MIN, FIREWORKS_VELOCITY_MAX));
		pEdict->v.iuser1 = RANDOM_LONG(FIREWORKS_MINLIFE, FIREWORKS_MAXLIFE);
		pEdict->v.iuser2 = r;
		pEdict->v.iuser3 = g;
		pEdict->v.iuser4 = b;
		SET_MODEL(pEdict, "models/rpgrocket.mdl");

		EMIT_SOUND(pEdict, CHAN_BODY, "../../chaos/firework_launch.wav", 1.0, ATTN_NORM);

		MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
		WRITE_BYTE(TE_BEAMFOLLOW);
		WRITE_SHORT(ENTINDEX(pEdict));
		WRITE_SHORT(m_iSprSmoke);
		WRITE_BYTE(45);
		WRITE_BYTE(4);
		WRITE_BYTE(r);
		WRITE_BYTE(g);
		WRITE_BYTE(b);
		WRITE_BYTE(255);
		MESSAGE_END();

		m_vFireworks.push_back(pEdict);
	}
}