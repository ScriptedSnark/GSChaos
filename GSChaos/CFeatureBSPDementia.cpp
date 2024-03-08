#include "includes.h"

void CFeatureBSPDementia::Init()
{
	CChaosFeature::Init();
}

void CFeatureBSPDementia::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	if (sv->worldmodel)
		m_pSurfaces = sv->worldmodel->surfaces;
	m_bActivated = true;
}

void CFeatureBSPDementia::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;
}

void CFeatureBSPDementia::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (!sv)
	{
		m_bActivated = false;
		return;
	}

	if (!sv->worldmodel)
	{
		m_bActivated = false;
		return;
	}

	if (!CLWrapper::GetWorldModel())
	{
		m_bActivated = false;
		return;
	}

	for (int i = 1; i < sv->worldmodel->numplanes; i++)
	{
		sv->worldmodel->planes[i].dist = 0;

		//sv->worldmodel->surfaces[i].plane->normal = m_pSurfaces[i].plane->normal + Vector(gChaos.GetRandomValue(-0.1f, 0.1f), gChaos.GetRandomValue(-0.1f, 0.1f), gChaos.GetRandomValue(-0.1f, 0.1f));
		//cl->worldmodel->surfaces[i].plane->normal = sv->worldmodel->surfaces[i].plane->normal;
		//cl->worldmodel->surfaces[i].plane->dist = sv->worldmodel->surfaces[i].plane->dist;
		//cl->worldmodel->vertexes[i].position = cl->worldmodel->vertexes[i].position + Vector(gChaos.GetRandomValue(.01f, 0.25f), gChaos.GetRandomValue(.01f, 0.25f), gChaos.GetRandomValue(.01f, 0.25f));
		//cl->worldmodel->planes[i].dist += gChaos.GetRandomValue(-1.5f, 1.5f);
	}
}

const char* CFeatureBSPDementia::GetFeatureName()
{
	//if (!cl_hl25)
	//	return "BSP Dementia (NOT SUPPORTED IN BUILD 8684)";
	//else
	return "BSP Dementia";
}