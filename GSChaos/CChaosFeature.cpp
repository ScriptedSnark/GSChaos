#include "includes.h"

std::vector<CChaosFeature*> gChaosFeatures;
std::vector<const char*> gChaosFeaturesNames; // hack

void CChaosFeature::Init()
{
	DEBUG_PRINT("CChaosFeature::Init\n");
}

void CChaosFeature::ActivateFeature()
{
	DEBUG_PRINT("CChaosFeature::ActivateFeature\n");
	DEBUG_PRINT("%s\n", GetFeatureName());

	m_bActivated = true;
}

void CChaosFeature::DeactivateFeature()
{
	DEBUG_PRINT("CChaosFeature::DeactivateFeature\n");
	m_bActivated = false;
}

void CChaosFeature::OnFrame(double time)
{
	;
}

const char* CChaosFeature::GetFeatureName()
{
	return "UNDEFINED";
}

void CChaosFeature::Draw()
{
	;
}

void CChaosFeature::ResetStates()
{
	;
}

bool CChaosFeature::IsActive()
{
	return m_bActivated;
}