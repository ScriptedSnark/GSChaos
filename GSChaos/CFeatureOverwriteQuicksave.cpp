#include "includes.h"

void CFeatureOverwriteQuicksave::Init()
{
	CChaosFeature::Init();
}

void CFeatureOverwriteQuicksave::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	SERVER_COMMAND(";save quick;\n");
}

void CFeatureOverwriteQuicksave::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureOverwriteQuicksave::GetFeatureName()
{
	return "Overwrite Quicksave";
}