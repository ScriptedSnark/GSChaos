#include "includes.h"

extern float* sys_timescale;

void CFeatureSuperhot::Init()
{
	CChaosFeature::Init();
}

void CFeatureSuperhot::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureSuperhot::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	*sys_timescale = 1.0f;
}

void CFeatureSuperhot::OnFrame(double time)
{
	if (!IsActive())
		return;
	
	static cvar_t* sv_maxspeed;
	if (!sv_maxspeed)
		sv_maxspeed = pEngfuncs->pfnGetCvarPointer("sv_maxspeed");

	float flMaxSpeed = sv_maxspeed ? sv_maxspeed->value : 320.0f;

	if (flMaxSpeed == 0)
		flMaxSpeed = 270.0f;

	float flVelocity = (*sv_player)->v.velocity.Length() / flMaxSpeed;
	*sys_timescale = std::clamp(flVelocity, 0.1f, 2.0f);
}

const char* CFeatureSuperhot::GetFeatureName()
{
	return "SUPERHOT";
}

double CFeatureSuperhot::GetDuration()
{
	return gChaos.GetChaosTime() * 1.06;
}

bool CFeatureSuperhot::UseCustomDuration()
{
	return true;
}

bool CFeatureSuperhot::CanBeInfinite()
{
	return true;
}