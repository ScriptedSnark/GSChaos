#include "includes.h"

void CFeaturePlayAG::Init()
{
	LoadTextureFromFile("chaos/playag.png", &m_iPlayAGID);
}

void CFeaturePlayAG::ActivateFeature()
{
	CFeatureForgotCSS::ActivateFeature();
}

int CFeaturePlayAG::GetTextureID()
{
	return m_iPlayAGID;
}

void CFeaturePlayAG::HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	CChaosFeature::HUD_AddEntity(type, ent, modelname);
}

const char* CFeaturePlayAG::GetFeatureName()
{
	return "Play AG";
}