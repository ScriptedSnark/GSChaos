#include "includes.h"

void CFeatureNoHUD::Init()
{
	CChaosFeature::Init();
}

void CFeatureNoHUD::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bDrawHUD = true;

#ifdef COF_BUILD
	hud_draw = pEngfuncs->pfnGetCvarPointer("hud_draw");
#endif
}

void CFeatureNoHUD::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bDrawHUD = false;

#ifdef COF_BUILD
	if (hud_draw)
		hud_draw->value = 1.0f;
#endif
}

#ifdef COF_BUILD
void CFeatureNoHUD::OnFrame(double time)
{
	if (!hud_draw)
		return;

	if (IsActive())
	{
		hud_draw->value = 0.0f;
	}
}
#endif

const char* CFeatureNoHUD::GetFeatureName()
{
	return "No HUD";
}