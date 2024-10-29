#include "includes.h"

void CFeatureMessWorld::Init()
{
	CChaosFeature::Init();
}

void CFeatureMessWorld::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureMessWorld::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureMessWorld::MessTextures()
{
	const char* levelName = CLWrapper::GetLevelName();

	if (levelName && levelName[0])
	{
		model_t* worldModel = CLWrapper::GetWorldModel();

		if (!worldModel)
			return;

		for (int i = 0; i < worldModel->numtextures; i++)
		{
			if (worldModel->textures[i])
			{
				worldModel->textures[i]->gl_texturenum = gChaos.GetRandomValue(1, 1000);
			}
		}
	}
}

void CFeatureMessWorld::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (m_flMessTime > gChaos.GetGlobalTime())
		return;

	m_flMessTime = gChaos.GetGlobalTime() + 1.5;
	MessTextures();
}

double CFeatureMessWorld::GetDuration()
{
	return gChaos.GetChaosTime() * 1.34;
}

bool CFeatureMessWorld::UseCustomDuration()
{
	return true;
}

const char* CFeatureMessWorld::GetFeatureName()
{
	return "Mess Up World";
}

bool CFeatureMessWorld::CanBeInfinite()
{
	return true;
}