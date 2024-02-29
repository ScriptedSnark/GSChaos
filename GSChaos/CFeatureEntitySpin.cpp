#include "includes.h"

void CFeatureEntitySpin::Init()
{
	CChaosFeature::Init();
}

void CFeatureEntitySpin::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;
}

void CFeatureEntitySpin::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;
}

void CFeatureEntitySpin::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	cl_entity_t* e;
	for (int i = 0; i < sv->num_edicts; i++)
	{
		e = pEngfuncs->GetEntityByIndex(i);
		if (e)
			e->curstate.angles = Vector(gChaos.GetRandomValue(-180, 180), gChaos.GetRandomValue(-180, 180), gChaos.GetRandomValue(-180, 180));
	}
}

const char* CFeatureEntitySpin::GetFeatureName()
{
	return "Entity spin";
}