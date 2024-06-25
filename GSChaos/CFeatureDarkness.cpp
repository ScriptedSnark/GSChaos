#include "includes.h"

void ShowHudMessage(edict_t* pEntity, const char* message)
{
	hudtextparms_t hudTextParams;
	hudTextParams.channel = 4;
	hudTextParams.x = -1.0;
	hudTextParams.y = 0.17;
	hudTextParams.effect = 1;
	hudTextParams.r1 = 255;
	hudTextParams.g1 = 0;
	hudTextParams.b1 = 0;
	hudTextParams.a1 = 0;
	hudTextParams.r2 = 255;
	hudTextParams.g2 = 0;
	hudTextParams.b2 = 0;
	hudTextParams.a2 = 0;
	hudTextParams.fadeinTime = 0.0;
	hudTextParams.fadeoutTime = 5.0;
	hudTextParams.holdTime = 1.0;
	hudTextParams.fxTime = 1.0;

	UTIL_HudMessage(pEntity, hudTextParams, message);
}

void CFeatureDarkness::Init()
{
	CChaosFeature::Init();
}

void CFeatureDarkness::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	
	pEngfuncs->pfnClientCmd(";spk .././chaos/darkness;\n");
	ShowHudMessage((*sv_player), "Be aware... Use your flashlight...");
	LIGHT_STYLE(0, "a");
}

void CFeatureDarkness::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	LIGHT_STYLE(0, "m");
}

const char* CFeatureDarkness::GetFeatureName()
{
	return "Darkness";
}

void CFeatureDarkness::Restore()
{
	if (IsActive())
		LIGHT_STYLE(0, "a");
}

double CFeatureDarkness::GetDuration()
{
	return gChaos.GetChaosTime() * 0.75;
}

bool CFeatureDarkness::UseCustomDuration()
{
	return true;
}