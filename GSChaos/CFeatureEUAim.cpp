#include "includes.h"

// Some parts are from HLAE (https://github.com/advancedfx/advancedfx) source code.
void MakeLocalCoords(Vector vAngles, Vector& vUp, Vector& vRight, Vector& vForward)
{
	// >> begin calculate transform vectors
	// we have to calculate our own transformation vectors from the angles and can not use pparams->forward etc., because in spectator mode they might be not present:
	// (adapted from HL1SDK/multiplayer/pm_shared.c/AngleVectors) and modified for quake order of angles:

	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = vAngles.y * ((float)M_PI * 2 / 360); // yaw
	sy = sin((float)angle);
	cy = cos((float)angle);
	angle = vAngles.x * ((float)M_PI * 2 / 360); // pitch
	sp = sin((float)angle);
	cp = cos((float)angle);
	angle = vAngles.z * ((float)M_PI * 2 / 360); // roll
	sr = sin((float)angle);
	cr = cos((float)angle);

	vForward.x = cp * cy;
	vForward.y = cp * sy;
	vForward.z = -sp;

	vRight.x = (-1 * sr * sp * cy + -1 * cr * -sy);
	vRight.y = (-1 * sr * sp * sy + -1 * cr * cy);
	vRight.z = -1 * sr * cp;

	vUp.x = (cr * sp * cy + -sr * -sy);
	vUp.y = (cr * sp * sy + -sr * cy);
	vUp.z = cr * cp;
}

void AnglesFromTo(Vector& from, Vector& to, Vector& angles)
{
	Vector dir = to - from;

	// Store then zero height
	float dz = dir.z;

	dir.z = 0;

	// Need this for later
	float length = dir.Length();

	dir = dir.Normalize();

	// This is our forward angle
	Vector vForward(1.0f, 0.0f, 0.0f);

	float dot_product = (dir.x * vForward.x) + (dir.y * vForward.y) + (dir.z * vForward.z);

	float angle = acos(dot_product) * 180.0f / (float)M_PI;

	if (dir.y < 0)
		angle = 360.0f - angle;

	// This is our pitchup/down
	if (length == 0)
		length = 0.01f;

	float pitch = atan(dz / length) * 180.0f / (float)M_PI;

	angles.x = angle;
	angles.y = -pitch;
}

bool IsEntityVisible(edict_t* pPlayer, edict_t* pEntity)
{
	TraceResult tr;
	Vector vecStart = pPlayer->v.origin + pPlayer->v.view_ofs;
	Vector vecEnd = pEntity->v.origin;

	UTIL_TraceLine(vecStart, vecEnd, dont_ignore_monsters, pPlayer, &tr);

	return (tr.flFraction == 1.0 || tr.pHit == pEntity);
}

edict_t* FindNearestEntity(edict_t* pPlayer, float& nearestDist)
{
	edict_t* pNearestEntity = nullptr;
	nearestDist = 8192.0f;

	for (int i = 1; i < gpGlobals->maxEntities; ++i)
	{
		edict_t* pEntity = ORIG_EDICT_NUM(i);

		if (pEntity && pEntity != pPlayer && pEntity->v.takedamage != DAMAGE_NO && (pEntity->v.flags & FL_MONSTER) && !(pEntity->v.effects & EF_NODRAW) && pEntity->v.movetype != MOVETYPE_TOSS && pEntity->v.health > 1)
		{
			if (!IsEntityVisible(pPlayer, pEntity))
				continue;

			float dist = (pEntity->v.origin - pPlayer->v.origin).Length();

			if (dist < nearestDist)
			{
				nearestDist = dist;
				pNearestEntity = pEntity;
			}
		}
	}

	return pNearestEntity;
}

void UpdateLockOn(edict_t* pPlayer)
{
	static edict_t* pLockedEntity = nullptr;
	static float nearestDist = 8192.0f;

	if (!pPlayer)
		return;

	float currentDist = 8192.0f;
	edict_t* pNearestEntity = FindNearestEntity(pPlayer, currentDist);

	if (pNearestEntity && (pLockedEntity == nullptr || currentDist < nearestDist))
	{
		pLockedEntity = pNearestEntity;
		nearestDist = currentDist;
	}

	if (pLockedEntity && pLockedEntity->v.deadflag == DEAD_NO && IsEntityVisible(pPlayer, pLockedEntity))
	{
		Vector angles;
		AnglesFromTo((*sv_player)->v.origin, pLockedEntity->v.origin, angles);

		float cangles[3];

		pEngfuncs->GetViewAngles(cangles);
		cangles[0] = angles.y;
		cangles[1] = angles.x;
		pEngfuncs->SetViewAngles(cangles);
	}
	else
	{
		pLockedEntity = nullptr;
		nearestDist = 8192.0f;
	}
}

void CFeatureEUAim::Init()
{
	CChaosFeature::Init();
}

void CFeatureEUAim::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureEUAim::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureEUAim::GetFeatureName()
{
	return "EU Aim";
}

void CFeatureEUAim::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!(*sv_player))
		return;

	if (!g_pRefParams)
		return;

	if (sv && sv->state != ss_active)
		return;

	// forgive me
	(*sv_player)->v.punchangle = Vector(0, 0, 0);
	*reinterpret_cast<Vector*>(g_pRefParams->punchangle) = Vector(0, 0, 0);

	UpdateLockOn((*sv_player));
}

double CFeatureEUAim::GetDuration()
{
	return gChaos.GetChaosTime() * 0.75;
}

bool CFeatureEUAim::UseCustomDuration()
{
	return true;	
}

bool CFeatureEUAim::CanBeInfinite()
{
	return true;
}