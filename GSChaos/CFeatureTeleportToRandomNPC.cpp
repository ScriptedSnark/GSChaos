#include "includes.h"

bool IsHullVacant(const Vector& origin, float hull, edict_t* player) {
	TraceResult tr;
	TRACE_HULL(origin, origin, ignore_monsters, hull, player, &tr);
	return !(tr.fStartSolid || tr.fAllSolid);
}

void CFeatureTeleportToRandomNPC::Init()
{
	CChaosFeature::Init();
}

void CFeatureTeleportToRandomNPC::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	edict_t* ent = ORIG_EDICT_NUM(gChaos.GetRandomValue(1, sv->num_edicts));
	int counter = 0;

	while (!(ent->v.flags & FL_MONSTER))
	{
		if (counter >= sv->num_edicts)
			break;

		counter++;
		ent = ORIG_EDICT_NUM(gChaos.GetRandomValue(1, sv->num_edicts));
	}

	if (ent && (ent->v.flags & FL_MONSTER))
	{
		(*sv_player)->v.origin = ent->v.origin;

		// just in case
		(*sv_player)->v.origin.z += 96.0f;
		DROP_TO_FLOOR((*sv_player));

		// TODO: implement unstuck func
	}
}

void CFeatureTeleportToRandomNPC::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureTeleportToRandomNPC::GetFeatureName()
{
	return "Teleport to random NPC";
}