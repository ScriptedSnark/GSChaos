#include "includes.h"

void CFeatureFly::Init()
{
	CChaosFeature::Init();
}

void CFeatureFly::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.velocity.z += 3999.0f; // weeeeeeee

	(*sv_player)->v.velocity.x += gChaos.GetRandomValue(-2000.0f, 2000.0f);
	(*sv_player)->v.velocity.y += gChaos.GetRandomValue(-2000.0f, 2000.0f);
}

void CFeatureFly::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureFly::GetFeatureName()
{
	return "I believe I can fly";
}