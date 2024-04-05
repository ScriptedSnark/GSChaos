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

const char* CFeaturePlayAG::GetFeatureName()
{
	return "Play AG";
}