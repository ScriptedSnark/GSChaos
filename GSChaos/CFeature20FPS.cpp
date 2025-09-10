#include "includes.h"

// VSync hack by @SmileyAG
typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALPROC)(int);
PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

void CFeature20FPS::Init()
{
	CChaosFeature::Init();

	fps_max = pEngfuncs->pfnGetCvarPointer("fps_max");
	fps_value = fps_max->value;

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");
}

void CFeature20FPS::ActivateFeature()
{
	if (!IsActive())
	{
		fps_max = pEngfuncs->pfnGetCvarPointer("fps_max");
		fps_value = fps_max->value;
		gl_vsync = pEngfuncs->pfnGetCvarPointer("gl_vsync");
		fps_override = pEngfuncs->pfnGetCvarPointer("fps_override");

		m_bVSyncEnabled = (gl_vsync && gl_vsync->value);
		m_bOverrideDisabled = (fps_override && !fps_override->value);
	}

	CChaosFeature::ActivateFeature();

	pEngfuncs->pfnClientCmd(UTIL_VarArgs(";fps_max %.01f;\n", g_bPreSteamPipe ? 20.0f : 19.5f));
	m_bActivated = true;

	if (m_bOverrideDisabled)
	{
		fps_override->value = 1.0f;
	}

	if (m_bVSyncEnabled)
	{
		if (wglSwapIntervalEXT)
			wglSwapIntervalEXT(0);
	}
}

void CFeature20FPS::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	fps_max->value = fps_value;
	pEngfuncs->pfnClientCmd(UTIL_VarArgs(";fps_max %.01f;\n", fps_value));

	if (m_bVSyncEnabled)
	{
		if (wglSwapIntervalEXT)
			wglSwapIntervalEXT(1);
	}

	if (m_bOverrideDisabled && fps_override->value)
	{
		fps_override->value = 0.0f;
	}
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