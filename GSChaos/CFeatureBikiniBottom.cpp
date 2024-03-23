#include "includes.h"

typedef int	(*_PM_PointContents) (vec3_t p, int* truecontents);

_PM_Move ORIG_PM_Move = NULL;
_PM_PointContents ORIG_PM_PointContents = NULL;

playermove_s* g_svpmove;

void CFeatureBikiniBottom::Init()
{
	CChaosFeature::Init();
}

int PM_PointContents(vec3_t p, int* truecontents)
{
	return CONTENTS_WATER;
}

// hack
void HOOKED_PM_Move(struct playermove_s* ppmove, qboolean server)
{
	static bool bHooked = false;
	if (!bHooked)
	{
		g_svpmove = ppmove;

		ORIG_PM_PointContents = ppmove->PM_PointContents;
		//g_svpmove->PM_PointContents = PM_PointContents;

		bHooked = true;
	}

	ORIG_PM_Move(ppmove, server);
}

void CFeatureBikiniBottom::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	if (g_svpmove)
		g_svpmove->PM_PointContents = PM_PointContents;
}

void CFeatureBikiniBottom::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	if (g_svpmove)
		g_svpmove->PM_PointContents = ORIG_PM_PointContents;
}

const char* CFeatureBikiniBottom::GetFeatureName()
{
	return "Bikini Bottom";
}