#include "includes.h"

void CFeaturePaperNPCs::ActivateFeature()
{
	CFeatureWideNPCs::ActivateFeature();
	SetCurrentTransformEffect(this);
}

const char* CFeaturePaperNPCs::GetFeatureName()
{
	return "Paper NPCs";
}

void CFeaturePaperNPCs::Transform(float transform[3][4])
{
	for (int i = 0; i < 3; ++i)
	{
		transform[i][1] *= 0.1f;
	}
}