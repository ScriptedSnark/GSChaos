#include "includes.h"

void CFeatureTinyNPCs::ActivateFeature()
{
	CFeatureWideNPCs::ActivateFeature();
	SetCurrentTransformEffect(this);
}

const char* CFeatureTinyNPCs::GetFeatureName()
{
	return "Tiny NPCs";
}

void CFeatureTinyNPCs::Transform(float transform[3][4])
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			transform[i][j] *= 0.5f;
		}
	}
}