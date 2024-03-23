#include "includes.h"

//===============
// PM code
//===============

// up / down
#define	PITCH	0
// left / right
#define	YAW		1
// fall over
#define	ROLL	2 

#undef vec3_t // for some reason that code is not friendly with Vector class (always returns 0,0,0)
typedef vec_t vec3_t[3];

typedef const char* (*_PM_Info_ValueForKey)(const char* s, const char* key);
_PM_Info_ValueForKey ORIG_PM_Info_ValueForKey = NULL;

void AngleVectors(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;

	angle = angles[YAW] * (M_PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[PITCH] * (M_PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[ROLL] * (M_PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp * cy;
		forward[1] = cp * sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1 * sr * sp * cy + -1 * cr * -sy);
		right[1] = (-1 * sr * sp * sy + -1 * cr * cy);
		right[2] = -1 * sr * cp;
	}
	if (up)
	{
		up[0] = (cr * sp * cy + -sr * -sy);
		up[1] = (cr * sp * sy + -sr * cy);
		up[2] = cr * cp;
	}
}

float VectorNormalize(vec3_t v)
{
	float	length, ilength;

	length = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	length = sqrt(length);		// FIXME

	if (length)
	{
		ilength = 1 / length;
		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}

	return length;

}

void VectorScale(const vec3_t in, vec_t scale, vec3_t out)
{
	out[0] = in[0] * scale;
	out[1] = in[1] * scale;
	out[2] = in[2] * scale;
}

void VectorAdd(vec3_t veca, vec3_t vecb, vec3_t out)
{
	out[0] = veca[0] + vecb[0];
	out[1] = veca[1] + vecb[1];
	out[2] = veca[2] + vecb[2];
}

// https://github.com/YaLTeR/halflife/blob/abh/pm_shared/pm_shared.c#L2605-L2628 (I don't count LJ because it's already too hackish)
void HL2_PM_Jump()
{
	float hSpeed, speedBoostPerc, speedAddition, maxSpeed, newSpeed;
	vec3_t fwd;
	AngleVectors(g_svpmove->angles, fwd, NULL, NULL);
	fwd[2] = 0;
	VectorNormalize(fwd);
	hSpeed = sqrt(g_svpmove->velocity[0] * g_svpmove->velocity[0] + g_svpmove->velocity[1] * g_svpmove->velocity[1]);

	speedBoostPerc = (!(g_svpmove->flags & FL_DUCKING)) ? 0.5f : 0.1f;
	speedAddition = fabs(g_svpmove->cmd.forwardmove * speedBoostPerc);
	maxSpeed = g_svpmove->maxspeed + (g_svpmove->maxspeed * speedBoostPerc);
	newSpeed = (speedAddition + hSpeed);

	if (newSpeed > maxSpeed)
		speedAddition -= newSpeed - maxSpeed;

	if (g_svpmove->cmd.forwardmove < 0.0f)
		speedAddition *= -1.0f;

	VectorScale(fwd, speedAddition, fwd);
	VectorAdd(fwd, g_svpmove->velocity, g_svpmove->velocity);
}

// HACK
// We need to perform HL2_PM_Jump code in PM_Jump environment but I'm too lazy to support million server DLLs so yeah...
// It can also mess player movement in other mods btw
const char* HOOKED_PM_Info_ValueForKey(const char* s, const char* key)
{
	const char* result = ORIG_PM_Info_ValueForKey(s, key);

	if (!stricmp(key, "slj"))
		HL2_PM_Jump();

	return result;
}

//===============
// Effect code
//===============
void CFeatureHL2Movement::Init()
{
	CChaosFeature::Init();
}

void CFeatureHL2Movement::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	if (!g_svpmove)
		return;

	ORIG_PM_Info_ValueForKey = g_svpmove->PM_Info_ValueForKey;
	g_svpmove->PM_Info_ValueForKey = HOOKED_PM_Info_ValueForKey;
}

void CFeatureHL2Movement::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	if (!g_svpmove)
		return;

	g_svpmove->PM_Info_ValueForKey = ORIG_PM_Info_ValueForKey;
}

const char* CFeatureHL2Movement::GetFeatureName()
{
	return "HL2 Movement";
}