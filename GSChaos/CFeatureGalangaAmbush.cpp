#include "includes.h"

void CFeatureGalangaAmbush::Init()
{
	CChaosFeature::Init();
}

void CFeatureGalangaAmbush::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_lastplayed = 0;
	m_curduration = 0;
	float pointsx[] = { 80, 56, 0, -56, -80, -56, 0, 56 };
	float pointsy[] = { 0, 56, 80, 56, 0, - 56, -80, -56 };
	float angles[] = { 180, 225, 270, 315, 0, 45, 90, 135 };

	Precache();
	for (int i = 0; i < 8; i++)
	{

		edict_t* galanga = CREATE_NAMED_ENTITY(MAKE_STRING("func_pushable"));
				
		if (!galanga)
		{
			DeactivateFeature();
			return;
		}
		KeyValueData kvm = KeyValueData{ "","material","1",0 };
		KeyValueData randomkeys[] = {
			KeyValueData{ "","explodemagnitude","80",0 },
			KeyValueData{ "","explodemagnitude","100",0 },
			KeyValueData{ "","explodemagnitude","50",0 },
			KeyValueData{ "","spawnobject","2",0 },
			KeyValueData{ "","spawnobject","1",0 }
		};

		
		galanga->v.spawnflags |= 128;
		galanga->v.friction = 390;
		gEntityInterface->pfnKeyValue(galanga, &randomkeys[gChaos.GetRandomValue(0,4)]);
		gEntityInterface->pfnKeyValue(galanga, &kvm);
		
		Vector playerOrigin = (*sv_player)->v.origin;
		playerOrigin.x = (int)playerOrigin.x + pointsx[i];
		playerOrigin.y = (int)playerOrigin.y + pointsy[i];
		playerOrigin.z += 8;
		gEntityInterface->pfnSpawn(galanga);

		galanga->v.targetname = MAKE_STRING("chaos_galanga");
		SET_MODEL(galanga, CHAOS_PATH "target_galanga.mdl");
		
		SET_SIZE(galanga, vec3_t(-16, -16, -36), vec3_t(16, 16, 36));
		galanga->v.angles = { 0, angles[i], 0 };
		SET_ORIGIN(galanga, playerOrigin);
		galanga->v.health = 50;
		m_vGalangas.push_back(galanga);
	}
	m_bSpawned = true;
}

void CFeatureGalangaAmbush::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	//m_vGalangas.clear();
	//m_bSpawned = false;
	//m_lastplayed = 0;
}

void CFeatureGalangaAmbush::OnFrame(double time)
{
	if (!m_bSpawned)
		return;
	double gtime = gChaos.GetGlobalTime();
	if (m_lastplayed + m_curduration > gtime) return;

	m_vGalangas.erase(
		std::remove_if(m_vGalangas.begin(), m_vGalangas.end(),
			[](edict_t* e) { return !UTIL_IsValidEntity(e) || strcmp(STRING(e->v.targetname), "chaos_galanga"); }),
		m_vGalangas.end()
	);
	if (m_vGalangas.empty()) {
		m_lastplayed = 0;
		m_bSpawned = false;
		DeactivateFeature();
		return;
	}
	galangese gal = galangaSounds[gChaos.GetRandomValue(0, 8)];
	m_lastplayed = gtime;
	m_curduration = gal.duration + gChaos.GetRandomValue((double)0.1, 0.3334f);

	for (auto&& galanga : m_vGalangas)
	{
		EMIT_SOUND_DYN2(galanga, CHAN_AUTO, gal.soundpath, 0.6, ATTN_NORM, 0, gChaos.GetRandomValue(90, 110));
	}
}

void CFeatureGalangaAmbush::Restore()
{
	m_vGalangas.erase(
		std::remove_if(m_vGalangas.begin(), m_vGalangas.end(),
			[](edict_t* e) { return !UTIL_IsValidEntity(e) || strcmp(STRING(e->v.targetname), "chaos_galanga"); }),
		m_vGalangas.end()
	);

	if (!IsActive() && m_vGalangas.empty())
		return;

	Precache();
}

const char* CFeatureGalangaAmbush::GetFeatureName()
{
	return "Galanga Ambush";
}

void CFeatureGalangaAmbush::Precache()
{
	PRECACHE_MODEL(CHAOS_PATH "target_galanga.mdl");
	for (auto&& sound : galangaSounds)
	{
		PRECACHE_SOUND(sound.soundpath);
	}
}

const CFeatureGalangaAmbush::galangese CFeatureGalangaAmbush::galangaSounds[9] = {
		{ "../../chaos/galanga/vortigese02.wav", 1.662 },
		{ "../../chaos/galanga/vortigese03.wav", 1.083 },
		{ "../../chaos/galanga/vortigese04.wav", 0.401 },
		{ "../../chaos/galanga/vortigese05.wav", 1.302 },
		{ "../../chaos/galanga/vortigese07.wav", 0.988 },
		{ "../../chaos/galanga/vortigese08.wav", 0.556 },
		{ "../../chaos/galanga/vortigese09.wav", 1.237 },
		{ "../../chaos/galanga/vortigese11.wav", 2.718 },
		{ "../../chaos/galanga/vortigese12.wav", 3.032 }
};