#include "includes.h"

void CFeatureReplaceModelsWithPlayer::Init()
{
	CChaosFeature::Init();
}

void CFeatureReplaceModelsWithPlayer::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
#ifdef COF_BUILD
	m_iSimonModel = PRECACHE_MODEL("models/cutscene/simon_talk2.mdl"); // HACK
#endif
}

void CFeatureReplaceModelsWithPlayer::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureReplaceModelsWithPlayer::GetFeatureName()
{
#ifdef COF_BUILD
	return "Replace models with Simon";
#else
	return "Replace models with player";
#endif
}

void CFeatureReplaceModelsWithPlayer::HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	if (ent->model->type != mod_studio)
		return;

#ifdef COF_BUILD
	if (pEngfuncs->hudGetModelByIndex(m_iSimonModel))
		ent->model = pEngfuncs->hudGetModelByIndex(m_iSimonModel);

	// just for fit
	if (type != 2) // TEMPENTITY
	{
		ent->origin.z += 16.f;
		ent->curstate.origin.z += 16.f;
	}
#else
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
#endif
}

double CFeatureReplaceModelsWithPlayer::GetDuration()
{
	return gChaos.GetChaosTime() * 2.5;
}

bool CFeatureReplaceModelsWithPlayer::UseCustomDuration()
{
	return true;
}

bool CFeatureReplaceModelsWithPlayer::CanBeInfinite()
{
	return true;
}