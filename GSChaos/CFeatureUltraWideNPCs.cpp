#include "includes.h"

void CFeatureUltraWideNPCs::ActivateFeature()
{
	CFeatureWideNPCs::ActivateFeature();
	SetCurrentTransformEffect(this);
}

const char* CFeatureUltraWideNPCs::GetFeatureName()
{
	return "Ultra wide NPCs";
}

float CFeatureUltraWideNPCs::GetScale()
{
	return 16.0f;
}