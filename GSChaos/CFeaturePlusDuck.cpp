#include "includes.h"

typedef void (*_CL_CreateMove)(float frametime, struct usercmd_s* cmd, int active);
_CL_CreateMove ORIG_CL_CreateMove = NULL;

bool g_bActivatedPlusDuck = false;

void HOOKED_CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	ORIG_CL_CreateMove(frametime, cmd, active);

	if (g_bActivatedPlusDuck)
		cmd->buttons |= IN_DUCK;
}

void CFeaturePlusDuck::Init()
{
	CChaosFeature::Init();
	int status;

	Find(Client, CL_CreateMove);
	CreateHook(Client, CL_CreateMove);
	MH_EnableHook(MH_ALL_HOOKS);
}

void CFeaturePlusDuck::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedPlusDuck = true;
}

void CFeaturePlusDuck::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedPlusDuck = false;
}

const char* CFeaturePlusDuck::GetFeatureName()
{
	return "+duck";
}

double CFeaturePlusDuck::GetDuration()
{
	return gChaos.GetChaosTime() * 1.25;
}

bool CFeaturePlusDuck::UseCustomDuration()
{
	return true;
}