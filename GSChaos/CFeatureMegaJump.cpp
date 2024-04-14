#include "includes.h"

void CFeatureMegaJump::Init()
{
	CChaosFeature::Init();
}

void CFeatureMegaJump::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureMegaJump::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureMegaJump::GetFeatureName()
{
	return "Mega Jump";
}

void CFeatureMegaJump::PM_Jump()
{
	(*sv_player)->v.velocity.z += 1337.f;
}