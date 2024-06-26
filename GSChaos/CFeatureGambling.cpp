#include "includes.h"

void CFeatureGambling::Init()
{
	CChaosFeature::Init();
}

void CFeatureGambling::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.health = gChaos.GetRandomValue(1, 255);
	(*sv_player)->v.armorvalue = gChaos.GetRandomValue(0, 255);
	// TODO: somehow change ammo value

	hudtextparms_t hudTextParams;
	hudTextParams.channel = 3;
	hudTextParams.x = -1.0;
	hudTextParams.y = 0.2;
	hudTextParams.effect = 2;
	hudTextParams.r1 = 255;
	hudTextParams.g1 = 160;
	hudTextParams.b1 = 0;
	hudTextParams.a1 = 0;
	hudTextParams.r2 = 255;
	hudTextParams.g2 = 160;
	hudTextParams.b2 = 0;
	hudTextParams.a2 = 0;
	hudTextParams.fadeinTime = 0.0;
	hudTextParams.fadeoutTime = 5.0;
	hudTextParams.holdTime = 1.0;
	hudTextParams.fxTime = 1.0;

	UTIL_HudMessage((*sv_player), hudTextParams, UTIL_VarArgs("You've got %d HP, %d armor!", (int)(*sv_player)->v.health, (int)(*sv_player)->v.armorvalue));

	if ((*sv_player)->v.health >= 245.0f && (*sv_player)->v.armorvalue >= 245.0f)
	{
		hudTextParams.effect = 1;
		hudTextParams.channel = 2;
		hudTextParams.holdTime = 5.0;
		hudTextParams.fxTime = 0.25;
		UTIL_HudMessage((*sv_player), hudTextParams, "JACKPOT !!!");

		for (auto& i : gChaosFeatures)
		{
			if (i->IsGood())
				i->ActivateFeature();
		}

		pEngfuncs->pfnClientCmd(";spk ../../chaos/lv_fruitwin;\n");
	}
	else
		pEngfuncs->pfnClientCmd(";spk ../../chaos/lv_fruit1;\n");
}

void CFeatureGambling::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureGambling::GetFeatureName()
{
	return "Gambling";
}