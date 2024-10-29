#include "includes.h"

void CFeatureOverwriteAutosave::Init()
{
	CChaosFeature::Init();
}

void CFeatureOverwriteAutosave::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	SERVER_COMMAND(";save autosave;\n");
}

void CFeatureOverwriteAutosave::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureOverwriteAutosave::GetFeatureName()
{
	return "Overwrite Autosave";
}