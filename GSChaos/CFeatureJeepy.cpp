#include "includes.h"

void CFeatureJeepy::Init()
{
	LoadTextureFromFile("chaos/jeepy.png", &m_iJeepyID);
}

void CFeatureJeepy::ActivateFeature()
{
	CFeatureForgotCSS::ActivateFeature();

	ma_engine_play_sound(&miniAudio, "chaos/lasagna.mp3", NULL);
}

int CFeatureJeepy::GetTextureID()
{
	return m_iJeepyID;
}

void CFeatureJeepy::HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	CChaosFeature::HUD_AddEntity(type, ent, modelname);
}

const char* CFeatureJeepy::GetFeatureName()
{
	return "Let's see Jeepy's lasagna";
}