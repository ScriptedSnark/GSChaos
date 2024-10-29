#include "includes.h"

void CFeatureTurbulentHell::Init()
{
	CChaosFeature::Init();
}

void CFeatureTurbulentHell::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureTurbulentHell::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	model_t* worldModel = CLWrapper::GetWorldModel();

	if (!worldModel)
		return;

	for (int i = 0; i < worldModel->numsurfaces; i++)
	{
		// I tried to check texture name, texture flags but water still changes with other geometry...
		// TODO: fix that mess - ScriptedSnark
		if (g_bHL25)
		{
			((msurface_HL25_t*)worldModel->surfaces)[i].flags &= ~SURF_DRAWTURB;
		}
		else
		{
			worldModel->surfaces[i].flags &= ~SURF_DRAWTURB;
		}
	}
}

void CFeatureTurbulentHell::R_DrawWorld()
{
	model_t* worldModel = CLWrapper::GetWorldModel();

	if (!worldModel)
		return;

	for (int i = 0; i < worldModel->numsurfaces; i++)
	{
		if (g_bHL25)
			((msurface_HL25_t*)worldModel->surfaces)[i].flags |= SURF_DRAWTURB;
		else
			worldModel->surfaces[i].flags |= SURF_DRAWTURB;
	}
}

const char* CFeatureTurbulentHell::GetFeatureName()
{
	return "Turbulent Hell";
}

double CFeatureTurbulentHell::GetDuration()
{
	return gChaos.GetChaosTime() * 1.1;
}

bool CFeatureTurbulentHell::UseCustomDuration()
{
	return true;
}

bool CFeatureTurbulentHell::CanBeInfinite()
{
	return true;
}