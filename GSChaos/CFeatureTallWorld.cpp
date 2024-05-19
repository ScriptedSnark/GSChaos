#include "includes.h"

void CFeatureTallWorld::Init()
{
	CChaosFeature::Init();
}

void CFeatureTallWorld::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureTallWorld::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureTallWorld::R_DrawWorld()
{
	glScalef(1.0f, 1.0f, 2.0f);
}

const char* CFeatureTallWorld::GetFeatureName()
{
	return "Tall World";
}

double CFeatureTallWorld::GetDuration()
{
	return gChaos.GetChaosTime() * 0.727;
}

bool CFeatureTallWorld::UseCustomDuration()
{
	return true;
}