#include "includes.h"

// Thanks to Admer456 for tempentities code
// https://github.com/Admer456/hl-sdk-videos-src/commit/fd7b4f1ca8d14eafb19431a3906f97dd86c962f5

void CFeatureTempEntityMadness::Init()
{
	CChaosFeature::Init();
}

void CFeatureTempEntityMadness::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_flTimeToSpawn = gChaos.GetGlobalTime() + 1.5;
}

void CFeatureTempEntityMadness::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureTempEntityMadness::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (!(*sv_player) || sv->state != ss_active)
	{
		m_flTimeToSpawn = gChaos.GetGlobalTime() + 0.5;
		return;
	}

	if (m_flTimeToSpawn < gChaos.GetGlobalTime())
	{
#ifdef COF_BUILD
		m_BeamSprite = PRECACHE_MODEL("sprites/lgtning.spr");
		m_FireSprite = PRECACHE_MODEL("sprites/fire.spr");
		m_SmokeSprite = PRECACHE_MODEL("sprites/steam1.spr");
		m_ShockwaveSprite = PRECACHE_MODEL("sprites/camera.spr");
		m_LightningSprite = PRECACHE_MODEL("sprites/xspark4.spr");
		m_GlowSprite = PRECACHE_MODEL("sprites/xspark4.spr");
		m_RockModel = PRECACHE_MODEL("models/simon_gibs.mdl"); // :D
		m_SkullModel = PRECACHE_MODEL("models/Facehead.mdl");
#else
		m_BeamSprite = PRECACHE_MODEL("sprites/lgtning.spr");
		m_FireSprite = PRECACHE_MODEL("sprites/fire.spr");
		m_SmokeSprite = PRECACHE_MODEL("sprites/steam1.spr");
		m_ShockwaveSprite = PRECACHE_MODEL("sprites/shockwave.spr");
		m_LightningSprite = PRECACHE_MODEL("sprites/xbeam5.spr");
		m_GlowSprite = PRECACHE_MODEL("sprites/xspark4.spr");
		m_RockModel = PRECACHE_MODEL("models/rockgibs.mdl");
		m_SkullModel = PRECACHE_MODEL("models/gib_skull.mdl");
#endif
		int value = gChaos.GetRandomValue(0, 23);
		switch (value)
		{
		case 0: TE_BeamPoints(); break;
		case 1: TE_Gunshot(); break;
		case 2: TE_Smoke(); break;
		case 3: TE_Tracer(); break;
		case 4: TE_Lightning(); break;
		case 5: TE_Sparks(); break;
		case 6: TE_Implosion(); break;
		case 7: TE_SpriteTrail(); break;
		case 8: TE_Sprite(); break;
		case 9: TE_BeamTorus(); break;
		case 10: TE_DLight(); break;
		case 11: TE_ELight(); break;
		case 12: TE_Line(); break;
		case 13: TE_LargeFunnel(); break;
		case 14: TE_BloodStream(); break;
		case 15: TE_Model(); break;
		case 16: TE_ExplodeModel(); break;
		case 17: TE_BreakModel(); break;
		case 18: TE_SpriteSpray(); break;
		case 19: TE_ArmorRicochet(); break;
		case 20: TE_Bubbles(); break;
		case 21: TE_BubbleTrail(); break;
		case 22: TE_ParticleBurst(); break;
		case 23: TE_FireField(); break;
		}
	}
}

void CFeatureTempEntityMadness::Restore()
{
	if (!IsActive())
		return;

	m_flTimeToSpawn = gChaos.GetGlobalTime() + 1.25; // we need some delay because engine can divide something by zero
}

const char* CFeatureTempEntityMadness::GetFeatureName()
{
	return "Temp Entity Madness";
}

double CFeatureTempEntityMadness::GetDuration()
{
	return gChaos.GetChaosTime() * 0.56;
}

bool CFeatureTempEntityMadness::UseCustomDuration()
{
	return true;
}

void CFeatureTempEntityMadness::TE_BeamPoints()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_BEAMPOINTS);
	WRITE_COORD((*sv_player)->v.origin.x); // start position
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.x); // end position
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z + 64.0f);
	WRITE_SHORT(m_BeamSprite); // sprite index
	WRITE_BYTE(0);			   // starting frame
	WRITE_BYTE(100);		   // frame rate in 0.1's
	WRITE_BYTE(60);			   // life in 0.1's
	WRITE_BYTE(50);			   // line width in 0.1's
	WRITE_BYTE(20);			   // noise amplitude in 0.01's
	WRITE_BYTE(255);		   // colour R
	WRITE_BYTE(160);		   // colour G
	WRITE_BYTE(0);			   // colour B
	WRITE_BYTE(255);		   // brightness
	WRITE_BYTE(50);			   // scroll speed in 0.1's

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Gunshot()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_GUNSHOT);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Smoke()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_SMOKE);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_SHORT(m_SmokeSprite); // smoke sprite index
	WRITE_BYTE(50);				// 5x scale
	WRITE_BYTE(10);				// 10fps

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Tracer()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_TRACER);
	WRITE_COORD((*sv_player)->v.origin.x - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD((*sv_player)->v.origin.x + 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Lightning()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_LIGHTNING);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z + 64.0f);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z - 64.0f);

	WRITE_BYTE(50);	 // 5 seconds of beam life
	WRITE_BYTE(200); // 20 units wide
	WRITE_BYTE(40);	 // 40% noise amplitude
	WRITE_SHORT(m_LightningSprite);

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Sparks()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_SPARKS);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Implosion()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_IMPLOSION);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_BYTE(200); // radius
	WRITE_BYTE(150); // count
	WRITE_BYTE(2);	 // 0.2 seconds of life

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_SpriteTrail()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_SPRITETRAIL);
	WRITE_COORD((*sv_player)->v.origin.x - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD((*sv_player)->v.origin.x + 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_SHORT(m_GlowSprite);
	WRITE_BYTE(150); // count
	WRITE_BYTE(2);	 // 0.2 seconds of life
	WRITE_BYTE(15);	 // 1.5x scale
	WRITE_BYTE(30);	 // 300 units/sec along vector
	WRITE_BYTE(2);	 // 20 units of randomness

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Sprite()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_SPRITE);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_SHORT(m_GlowSprite);
	WRITE_BYTE(10);	 // 1x scale
	WRITE_BYTE(100); // about 40% brightness

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_BeamTorus()
{
	for (int i = 1; i <= 4; i++)
	{
		MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, (*sv_player)->v.origin);

		WRITE_BYTE(TE_BEAMCYLINDER);
		WRITE_COORD((*sv_player)->v.origin.x);
		WRITE_COORD((*sv_player)->v.origin.y);
		WRITE_COORD((*sv_player)->v.origin.z - 32.0f + (i * 16.0f));
		WRITE_COORD((*sv_player)->v.origin.x);
		WRITE_COORD((*sv_player)->v.origin.y);
		WRITE_COORD((*sv_player)->v.origin.z + (1200.0f / i)); // point up, radius 1000 units
		WRITE_SHORT(m_BeamSprite);
		WRITE_BYTE(i);				// starting frame
		WRITE_BYTE(250);			// 25 fps
		WRITE_BYTE(20 + (i * 3));	// 2.3 then 2.6 seconds of life
		WRITE_BYTE(50);				// 5 units wide
		WRITE_BYTE(0);				// no noise (doesn't work)
		WRITE_BYTE(230 + (i * 4));	// colour R
		WRITE_BYTE(220 - (i * 10)); // colour G
		WRITE_BYTE(210 - (i * 30)); // colour B
		WRITE_BYTE(255);			// brightness
		WRITE_BYTE(0);				// don't scroll (doesn't work)

		MESSAGE_END();
	}
}

void CFeatureTempEntityMadness::TE_DLight()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_DLIGHT);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_BYTE(20);	 // 200 units of radius
	WRITE_BYTE(255); // colour R
	WRITE_BYTE(100); // colour G
	WRITE_BYTE(100); // colour B
	WRITE_BYTE(160); // brightness
	WRITE_BYTE(10);	 // 100 units of "life"
	WRITE_BYTE(1);	 // decay 10 units per second, affects radius

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_ELight()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_ELIGHT);
	WRITE_SHORT(0); // Do not follow any entity
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD(200); // 200 units of radius
	WRITE_BYTE(255);  // colour R
	WRITE_BYTE(100);  // colour G
	WRITE_BYTE(100);  // colour B
	WRITE_BYTE(10);	  // 100 units of "life"
	WRITE_COORD(10);  // decay 10 units per second, affects radius

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Line()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_LINE);
	WRITE_COORD((*sv_player)->v.origin.x - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD((*sv_player)->v.origin.x + 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_SHORT(10); // 1 second of life
	WRITE_BYTE(255); // colour R
	WRITE_BYTE(255); // colour G
	WRITE_BYTE(255); // colour B

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Box()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_BOX);
	WRITE_COORD((*sv_player)->v.origin.x - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y - 32.0f);
	WRITE_COORD((*sv_player)->v.origin.z - 16.0f);
	WRITE_COORD((*sv_player)->v.origin.x + 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y + 32.0f);
	WRITE_COORD((*sv_player)->v.origin.z + 64.0f);
	WRITE_SHORT(10); // 1 second of life
	WRITE_BYTE(255); // colour R
	WRITE_BYTE(255); // colour G
	WRITE_BYTE(255); // colour B

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_LargeFunnel()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_LARGEFUNNEL);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_SHORT(m_GlowSprite);
	WRITE_SHORT(0); // flag 1 = go in reverse

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_BloodStream()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_BLOODSTREAM);
	WRITE_COORD((*sv_player)->v.origin.x); // start position
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD(0.5f); // spray vector
	WRITE_COORD(0.0f);
	WRITE_COORD(0.5f);
	WRITE_BYTE(71);	 // colour from the engine's colour palette (71 is really red)
	WRITE_BYTE(150); // speed

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Model()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_MODEL);
	WRITE_COORD((*sv_player)->v.origin.x); // starting position
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD(20.0f); // velocity
	WRITE_COORD(0.0f);
	WRITE_COORD(100.0f);
	WRITE_ANGLE(0.0f);			 // initial yaw
	WRITE_SHORT(m_RockModel);	 // model index
	WRITE_BYTE(BOUNCE_CONCRETE); // bounce sound type
	WRITE_BYTE(100);			 // 10 seconds of life

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_ExplodeModel()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_EXPLODEMODEL);
	WRITE_COORD((*sv_player)->v.origin.x); // starting position
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD(500.0f);	   // velocity
	WRITE_SHORT(m_SkullModel); // model index
	WRITE_SHORT(50);		   // count
	WRITE_BYTE(40);			   // 4 seconds of life

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_BreakModel()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_BREAKMODEL);
	WRITE_COORD((*sv_player)->v.origin.x); // starting position
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD(100.0f); // bbox size
	WRITE_COORD(100.0f);
	WRITE_COORD(100.0f);
	WRITE_COORD(0.0f); // velocity
	WRITE_COORD(0.0f);
	WRITE_COORD(200.0f);
	WRITE_BYTE(4);				// 40 units of randomness
	WRITE_SHORT(m_RockModel);	// model index
	WRITE_BYTE(0);				// count - let the client decide
	WRITE_BYTE(40);				// 4 seconds of life
	WRITE_BYTE(BREAK_CONCRETE); // flags

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_SpriteSpray()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_SPRITE_SPRAY);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD(0.0f);
	WRITE_COORD(0.0f);
	WRITE_COORD(100.0f);
	WRITE_SHORT(m_GlowSprite);
	WRITE_BYTE(50); // count
	WRITE_BYTE(10); // speed??
	WRITE_BYTE(20); // noise

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_ArmorRicochet()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_ARMOR_RICOCHET);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_BYTE(10); // 1x scale

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_Bubbles()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_BUBBLES);
	WRITE_COORD((*sv_player)->v.origin.x - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.z - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.x + 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y + 64.0f);
	WRITE_COORD((*sv_player)->v.origin.z + 64.0f);
	WRITE_COORD(100.0f); // float up to 50 units
	WRITE_SHORT(m_SmokeSprite);
	WRITE_BYTE(50);		// 50 of em
	WRITE_COORD(50.0f); // speed

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_BubbleTrail()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_BUBBLETRAIL);
	WRITE_COORD((*sv_player)->v.origin.x - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y - 64.0f);
	WRITE_COORD((*sv_player)->v.origin.z - 8.0f);
	WRITE_COORD((*sv_player)->v.origin.x + 64.0f);
	WRITE_COORD((*sv_player)->v.origin.y + 64.0f);
	WRITE_COORD((*sv_player)->v.origin.z + 8.0f);
	WRITE_COORD(100.0f); // float up to 50 units
	WRITE_SHORT(m_SmokeSprite);
	WRITE_BYTE(50);		// 50 of em
	WRITE_COORD(50.0f); // speed

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_ParticleBurst()
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

	WRITE_BYTE(TE_PARTICLEBURST);
	WRITE_COORD((*sv_player)->v.origin.x);
	WRITE_COORD((*sv_player)->v.origin.y);
	WRITE_COORD((*sv_player)->v.origin.z);
	WRITE_COORD(50.0f);			 // radius
	WRITE_BYTE(71); // colour
	WRITE_BYTE(10);				 // duration

	MESSAGE_END();
}

void CFeatureTempEntityMadness::TE_FireField()
{
	// Also trace to the ground
	TraceResult tr;
	UTIL_TraceLine((*sv_player)->v.origin, (*sv_player)->v.origin - Vector(0.0f, 0.0f, 100.0f), ignore_monsters, (*sv_player), &tr);

	// This loop is a chunky one, it sends 110 bytes total
	// It would be better to spawn this dynamically, in phases, in some Think method
	for (int i = 0; i < 10; i++)
	{
		MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, (*sv_player)->v.origin);

		WRITE_BYTE(TE_FIREFIELD);
		WRITE_COORD(tr.vecEndPos.x);
		WRITE_COORD(tr.vecEndPos.y);
		// offset the Z a little bit so the fire mostly isn't inside the ground
		WRITE_COORD(tr.vecEndPos.z + 30.0f - float(i * 2));
		WRITE_SHORT(64 + (i * 24)); // radius
		WRITE_SHORT(m_FireSprite);
		WRITE_BYTE(20);						// count; will be 200 total
		WRITE_BYTE(TEFIRE_FLAG_LOOP			// loop at 15fps
			| TEFIRE_FLAG_PLANAR		// spawn on a flat plane
			| TEFIRE_FLAG_ADDITIVE); // additive render mode
		WRITE_BYTE(150 + (i * 10));			// inner ring -> 15 secs; outer ring -> 24 secs

		MESSAGE_END();
	}
}