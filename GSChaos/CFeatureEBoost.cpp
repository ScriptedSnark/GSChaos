#include "includes.h"

void CFeatureEBoost::Init()
{
	CChaosFeature::Init();
}

void CFeatureEBoost::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureEBoost::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureEBoost::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!(*sv_player))
		return;

	if (!g_svpmove)
		return;

	Vector fwd;
	pEngfuncs->pfnAngleVectors(g_svpmove->angles, fwd, NULL, NULL);

	fwd.Normalize();

	float zVel = (*sv_player)->v.velocity[2];
	if (cmd->buttons & IN_USE) // we do a little trolling here because +use slows down player
	{
		(*sv_player)->v.velocity = (*sv_player)->v.velocity + fwd * 15;
		(*sv_player)->v.velocity[2] = zVel;
	}
}

const char* CFeatureEBoost::GetFeatureName()
{
	return "Hold +USE to boost!";
}

double CFeatureEBoost::GetDuration()
{
	return gChaos.GetChaosTime() * 1.25;
}

bool CFeatureEBoost::UseCustomDuration()
{
	return true;
}

bool CFeatureEBoost::CanBeInfinite()
{
	return true;
}