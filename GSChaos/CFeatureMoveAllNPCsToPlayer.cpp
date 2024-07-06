#include "includes.h"

void CFeatureMoveAllNPCsToPlayer::Init()
{
	CChaosFeature::Init();
}

void CFeatureMoveAllNPCsToPlayer::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	for (int i = 1; i < sv->num_edicts; i++)
	{
		edict_t* e = ORIG_EDICT_NUM(i);

		if (!e)
			continue;

		if (!(e->v.flags & FL_MONSTER))
			continue;

		if (!strstr(STRING(e->v.classname), "monster"))
			continue;

		if (strstr(STRING(e->v.classname), "osprey")) // we don't need any crashes
			continue;

		UTIL_MakeVectors((*sv_player)->v.angles);
		e->v.origin = (*sv_player)->v.origin + gpGlobals->v_right * 64 + gpGlobals->v_forward * 32;
		(*sv_player)->v.velocity = Vector(0, 0, 0); // just to not be stuck (doesn't matter, we'll stuck anyway :xdd:)
	}

	SERVER_COMMAND(";save chaos;load chaos;\n"); // TOO LAZY TO HOOK SOMETHING LIKE SV_SendClientDatagram
}

void CFeatureMoveAllNPCsToPlayer::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureMoveAllNPCsToPlayer::GetFeatureName()
{
	return "Move all NPCs to player";
}