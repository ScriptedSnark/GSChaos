#include "includes.h"

typedef int	(*_PM_PointContents) (vec3_t p, int* truecontents);
typedef const char* (*_PM_Info_ValueForKey)(const char* s, const char* key);

_PM_PointContents ORIG_PM_PointContents = NULL;
_PM_Info_ValueForKey ORIG_PM_Info_ValueForKey = NULL;

_PM_Move ORIG_PM_Move = NULL;
playermove_s* g_svpmove;

bool g_bActivatedBikiniBottom;
bool g_bActivatedDisableWater;

// HACK
// We need to perform HL2_PM_Jump code in PM_Jump environment but I'm too lazy to support million server DLLs so yeah...
// It can also mess player movement in other mods btw
const char* HOOKED_PM_Info_ValueForKey(const char* s, const char* key)
{
	const char* result = ORIG_PM_Info_ValueForKey(s, key);

	if (!stricmp(key, "slj"))
	{
		for (CChaosFeature* i : gChaosFeatures)
		{
			if (i->IsActive())
				i->PM_Jump();
		}
	}

	return result;
}

int PM_PointContents(vec3_t p, int* truecontents)
{
	if (g_bActivatedBikiniBottom)
		return CONTENTS_WATER;

	if (g_bActivatedDisableWater)
		return CONTENTS_SOLID;

	return ORIG_PM_PointContents(p, truecontents);
}

// hack
void HOOKED_PM_Move(struct playermove_s* ppmove, qboolean server)
{
	static bool bHooked = false;
	if (!bHooked)
	{
		g_svpmove = ppmove;

		if (g_bEncrypted)
			MemUtils::MarkAsExecutable(g_svpmove->PM_Info_ValueForKey);

		MH_STATUS status = MH_CreateHook(g_svpmove->PM_Info_ValueForKey, HOOKED_PM_Info_ValueForKey, reinterpret_cast<void**>(&ORIG_PM_Info_ValueForKey));
		if (status != MH_OK)
			DEBUG_PRINT("[hw dll] Couldn't create hook for g_svpmove->PM_Info_ValueForKey.\n");

		if (g_bEncrypted)
			MemUtils::MarkAsExecutable(g_svpmove->PM_PointContents);

		status = MH_CreateHook(g_svpmove->PM_PointContents, PM_PointContents, reinterpret_cast<void**>(&ORIG_PM_PointContents));
		if (status != MH_OK)
			DEBUG_PRINT("[hw dll] Couldn't create hook for g_svpmove->PM_Info_ValueForKey.\n");

		MH_EnableHook(MH_ALL_HOOKS);
		bHooked = true;
	}

	for (CChaosFeature* i : gChaosFeatures)
	{
		if (!i->IsActive())
			continue;

		i->PM_Move(ppmove, server);
	}

	ORIG_PM_Move(ppmove, server);
}

void CFeatureBikiniBottom::Init()
{
	CChaosFeature::Init();
}

void CFeatureBikiniBottom::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedBikiniBottom = true;
}

void CFeatureBikiniBottom::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedBikiniBottom = false;
}

void CFeatureBikiniBottom::OnFrame(double time)
{
	if (!IsActive())
		return;

	// https://github.com/ValveSoftware/halflife/blob/master/dlls/player.cpp#L1206
	(*sv_player)->v.pain_finished = gpGlobals->time + 1; // disable drowning damage
}

const char* CFeatureBikiniBottom::GetFeatureName()
{
	return "Bikini Bottom";
}

double CFeatureBikiniBottom::GetDuration()
{
	return gChaos.GetChaosTime() * 1.45;
}

bool CFeatureBikiniBottom::UseCustomDuration()
{
	return true;
}

bool CFeatureBikiniBottom::CanBeInfinite()
{
	return true;
}