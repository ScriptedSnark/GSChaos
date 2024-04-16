#include "includes.h"

void CFeatureReplaceModelsWithPlayer::Init()
{
	CChaosFeature::Init();
}

void CFeatureReplaceModelsWithPlayer::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureReplaceModelsWithPlayer::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureReplaceModelsWithPlayer::GetFeatureName()
{
	return "Replace models with player";
}

void CFeatureReplaceModelsWithPlayer::HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	if (ent->model->type != mod_studio)
		return;

	cl_entity_s* player = pEngfuncs->GetLocalPlayer();
	ent->model = player->model;
	ent->curstate.modelindex = player->curstate.modelindex;
	ent->curstate.gaitsequence = ent->curstate.sequence;
	// just for fit
	if (type != 2) // TEMPENTITY
	{
		ent->origin.z += 36.f;
		ent->curstate.origin.z += 36.f;
	}
}

double CFeatureReplaceModelsWithPlayer::GetDuration()
{
	return gChaos.GetChaosTime() * 2.5;
}

bool CFeatureReplaceModelsWithPlayer::UseCustomDuration()
{
	return true;
}