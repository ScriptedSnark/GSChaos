#include "includes.h"

void CFeature20FPS::Init()
{
	CChaosFeature::Init();

	fps_max = pEngfuncs->pfnGetCvarPointer("fps_max");
	fps_value = fps_max->value;
}

void CFeature20FPS::ActivateFeature()
{
	if (!IsActive())
	{
		fps_max = pEngfuncs->pfnGetCvarPointer("fps_max");
		fps_value = fps_max->value;
	}

	CChaosFeature::ActivateFeature();

	pEngfuncs->pfnClientCmd(UTIL_VarArgs(";fps_max %.01f;\n", g_bPreSteamPipe ? 20.0f : 19.5f));
	m_bActivated = true;
}

void CFeature20FPS::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	fps_max->value = fps_value;
	pEngfuncs->pfnClientCmd(UTIL_VarArgs(";fps_max %.01f;\n", fps_value));
}

void CFeature20FPS::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	fps_max->value = g_bPreSteamPipe ? 20.0f : 19.5f;
}

const char* CFeature20FPS::GetFeatureName()
{
	return "Force 20 FPS";
}

double CFeature20FPS::GetDuration()
{
	return gChaos.GetChaosTime() * 1.05;
}

bool CFeature20FPS::UseCustomDuration()
{
	return true;
}