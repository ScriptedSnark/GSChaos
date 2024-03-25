#include "includes.h"

void CFeatureNodeGraphRebuilding::Init()
{
	CChaosFeature::Init();
}

void CFeatureNodeGraphRebuilding::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_flStartTime = gChaos.GetGlobalTime() + 1.0;
	g_engfuncs->pfnClientPrintf((*sv_player), print_center, "Node Graph out of Date. Rebuilding...");
}

void CFeatureNodeGraphRebuilding::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_flStartTime = gChaos.GetGlobalTime() + 1.0; // just in case
}

void CFeatureNodeGraphRebuilding::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (gChaos.GetGlobalTime() > m_flStartTime)
	{
		Sleep(2000); // we're rebuilding node graph, don't worry
		DeactivateFeature();
		g_engfuncs->pfnClientPrintf((*sv_player), print_center, "Thanks for your patience! :DDDDDDDD");
	}
}

const char* CFeatureNodeGraphRebuilding::GetFeatureName()
{
	return "Node Graph";
}