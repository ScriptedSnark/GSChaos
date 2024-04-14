#include "includes.h"

void CFeatureReloadAutosave::Init()
{
	CChaosFeature::Init();
}

void CFeatureReloadAutosave::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	SERVER_COMMAND(";load autosave;\n");
}

void CFeatureReloadAutosave::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureReloadAutosave::GetFeatureName()
{
	return "Reload Autosave";
}