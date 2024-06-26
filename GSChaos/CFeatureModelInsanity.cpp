#include "includes.h"

void CFeatureModelInsanity::ActivateFeature()
{
	CFeatureWideNPCs::ActivateFeature();
	SetCurrentTransformEffect(this);
}

const char* CFeatureModelInsanity::GetFeatureName()
{
	return "Model Insanity";
}

void CFeatureModelInsanity::Transform(float transform[3][4])
{
	float currentTime = (float)gChaos.GetGlobalTime();

	for (int i = 0; i < 3; ++i)
	{
		transform[i][1] *= (1.0f + 1.75f * std::sin(currentTime + i)) * 2.0f;
		transform[i][2] *= (1.0f + 1.75f * std::cos(currentTime + i)) * 2.0f;
	}
}