#include "includes.h"

void CFeatureHigh::Init()
{
	CChaosFeature::Init();
}

void CFeatureHigh::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedShader = true;

	if (pEngfuncs->pfnGetCvarFloat("gl_use_shaders"))
	{
		m_bDetectedEngineShaders = true;
		g_engfuncs->pfnClientPrintf((*sv_player), print_center, "Disabled \"gl_use_shaders\" so High works.");
		pEngfuncs->pfnClientCmd(";gl_use_shaders 0;\n");
	}
	else
		m_bDetectedEngineShaders = false;
}

void CFeatureHigh::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedShader = false;

	if (m_bDetectedEngineShaders)
		pEngfuncs->pfnClientCmd(";gl_use_shaders 1;\n");
}

const char* CFeatureHigh::GetFeatureName()
{
	return "High";
}

double CFeatureHigh::GetDuration()
{
	return gChaos.GetChaosTime() * 0.5;
}

bool CFeatureHigh::UseCustomDuration()
{
	return true;
}