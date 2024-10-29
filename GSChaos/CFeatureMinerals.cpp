#include "includes.h"

void CFeatureMinerals::Init()
{
	CChaosFeature::Init();
}

void CFeatureMinerals::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_iCrystalModel = PRECACHE_MODEL(CHAOS_PATH "crystal.mdl"); // HACK
}

void CFeatureMinerals::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureMinerals::HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	if (ent->model->type != mod_studio)
		return;

	if (pEngfuncs->hudGetModelByIndex(m_iCrystalModel))
		ent->model = pEngfuncs->hudGetModelByIndex(m_iCrystalModel);
}

void CFeatureMinerals::Restore()
{
	if (IsActive())
		DeactivateFeature();
}

const char* CFeatureMinerals::GetFeatureName()
{
	return "Minerals";
}

double CFeatureMinerals::GetDuration()
{
	return gChaos.GetChaosTime() * 0.675;
}

bool CFeatureMinerals::UseCustomDuration()
{
	return true;
}

bool CFeatureMinerals::CanBeInfinite()
{
	return true;
}