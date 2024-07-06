#include "includes.h"

// stupid surface struct, WHYYYYYYYYYYYYYYYYYYYYYYYY
typedef float (*_ScrollOffsetHL25)(msurface_HL25_t* psurface, cl_entity_t* pEntity);
typedef float (*_ScrollOffset)(msurface_t* psurface, cl_entity_t* pEntity);
_ScrollOffsetHL25 ORIG_ScrollOffsetHL25 = NULL;
_ScrollOffset ORIG_ScrollOffset = NULL;

bool g_bScrollingHell;

float ScrollOffset(float width)
{
	// I had to do the same thing engine does but in hardcoded way
	// WITHOUT HOOKING THIS EFFECT WON'T WORK!!!! - ScriptedSnark
	float offset = (float)(25 + (25 << 8)) / 16.0f;
	float speed = 1.0f / width * offset * pEngfuncs->GetClientTime();

	return fmod(speed, 1);
}

float HOOKED_ScrollOffset(msurface_t* psurface, cl_entity_t* pEntity)
{
	if (!psurface)
		return 1.0f;

	if (g_bScrollingHell)
		return ScrollOffset(psurface->texinfo->texture->width);

	return ORIG_ScrollOffset(psurface, pEntity);
}

float HOOKED_ScrollOffsetHL25(msurface_HL25_t* psurface, cl_entity_t* pEntity)
{
	if (g_bScrollingHell)
		return ScrollOffset(psurface->texinfo->texture->width);

	return ORIG_ScrollOffsetHL25(psurface, pEntity);
}

void CFeatureScrollingHell::Init()
{
	CChaosFeature::Init();
	int status;

	if (g_bHL25)
	{
		SPTFind(ScrollOffsetHL25);
		EngineCreateHook(ScrollOffsetHL25);
	}
	else
	{
		SPTFind(ScrollOffset);
		EngineCreateHook(ScrollOffset);
	}

	MH_EnableHook(MH_ALL_HOOKS);
}

void CFeatureScrollingHell::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bScrollingHell = true;
}

void CFeatureScrollingHell::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	model_t* worldModel = CLWrapper::GetWorldModel();

	if (!worldModel)
		return;

	for (int i = 0; i < worldModel->numsurfaces; i++)
	{
		if (g_bHL25)
		{
			((msurface_HL25_t*)worldModel->surfaces)[i].flags &= ~SURF_DRAWTILED;
		}
		else
		{
			worldModel->surfaces[i].flags &= ~SURF_DRAWTILED;
		}
	}

	g_bScrollingHell = false;
}

void CFeatureScrollingHell::R_DrawWorld()
{
	model_t* worldModel = pEngfuncs->GetEntityByIndex(0)->model;

	if (!worldModel)
		return;

	for (int i = 0; i < worldModel->numsurfaces; i++)
	{
		if (g_bHL25)
			((msurface_HL25_t*)worldModel->surfaces)[i].flags |= SURF_DRAWTILED;
		else
			worldModel->surfaces[i].flags |= SURF_DRAWTILED;
	}
}

const char* CFeatureScrollingHell::GetFeatureName()
{
	return "Scrolling Hell";
}

double CFeatureScrollingHell::GetDuration()
{
	return gChaos.GetChaosTime() * 0.64;
}

bool CFeatureScrollingHell::UseCustomDuration()
{
	return true;
}