#include "includes.h"

// From engine's mathlib.c
float Length(const vec3_t v)
{
	int i;
	float length;

	length = 0;
	for (i = 0; i < 3; i++)
		length += v[i] * v[i];
	length = static_cast<float>(sqrt(length)); // FIXME

	return length;
}

void CFeatureGravityField::Init()
{
	CChaosFeature::Init();
}

void CFeatureGravityField::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;
}

void CFeatureGravityField::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;
}

void CFeatureGravityField::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (CLWrapper::GetPausedState())
		return;

	// point of no return
	edict_t* e;
	for (int i = 1; i < sv->num_edicts; i++)
	{
		e = ORIG_EDICT_NUM(i);
		if (e && !e->free)
		{
			if (e->v.flags & FL_CLIENT)
				continue;

			(*sv_player)->v.flags |= FL_GODMODE; // this effect is too crazy for player's health :DDD

			Vector target = (*sv_player)->v.origin - e->v.origin;

			float distance = Length(target);
			Vector direction = target / distance;
			Vector velocity = direction * MAGNET_SPEED;

			e->v.velocity = velocity;
		}
	}
}

const char* CFeatureGravityField::GetFeatureName()
{
	return "Hyper Gravity Field";
}