#include "includes.h"

void CFeatureJeepy::Init()
{
	LoadTextureFromFile("chaos/jeepy.png", &m_iJeepyID);
}

void CFeatureJeepy::ActivateFeature()
{
	CFeatureForgotCSS::ActivateFeature();

	ma_engine_set_volume(&miniAudio, CVAR_GET_FLOAT("volume"));
	ma_engine_play_sound(&miniAudio, "chaos/lasagna.mp3", NULL);
}

int CFeatureJeepy::GetTextureID()
{
	return m_iJeepyID;
}

const char* CFeatureJeepy::GetFeatureName()
{
	return "Let's see Jeepy's lasagna";
}