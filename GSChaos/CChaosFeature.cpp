#include "includes.h"

std::vector<CChaosFeature*> gChaosFeatures;
std::vector<const char*> gChaosFeaturesNames; // hack

void CChaosFeature::Init()
{
	DEBUG_PRINT("CChaosFeature::Init\n");
}

void CChaosFeature::ActivateFeature()
{
	DEBUG_PRINT("CChaosFeature::ActivateFeature\n");
	DEBUG_PRINT("%s\n", GetFeatureName());
}

void CChaosFeature::DeactivateFeature()
{
	DEBUG_PRINT("CChaosFeature::DeactivateFeature\n");
}

void CChaosFeature::OnFrame(double time)
{
	;
}

const char* CChaosFeature::GetFeatureName()
{
	return "UNDEFINED";
}

void CChaosFeature::Draw()
{
	;
}