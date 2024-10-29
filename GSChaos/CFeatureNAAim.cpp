#include "includes.h"

void CFeatureNAAim::Init()
{
	CChaosFeature::Init();
}

void CFeatureNAAim::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureNAAim::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureNAAim::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!(*sv_player))
		return;

	if ((cmd->buttons & IN_ATTACK) || (cmd->buttons & IN_ATTACK2))
		(*sv_player)->v.punchangle += Vector(gChaos.GetRandomValue(-3.5f, 2.5f), 0, gChaos.GetRandomValue(-3.5f, 2.5f));
}

const char* CFeatureNAAim::GetFeatureName()
{
	return "NA Aim";
}

double CFeatureNAAim::GetDuration()
{
	return gChaos.GetChaosTime() * 1.25;
}

bool CFeatureNAAim::UseCustomDuration()
{
	return true;
}

bool CFeatureNAAim::CanBeInfinite()
{
	return true;
}