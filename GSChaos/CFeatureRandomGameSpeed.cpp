#include "includes.h"

void CFeatureRandomGameSpeed::ActivateFeature()
{
	CFeatureHalfGameSpeed::ActivateFeature();
	m_flGameSpeed = gChaos.GetRandomValue(0.01f, 4.50f);
}

const char* CFeatureRandomGameSpeed::GetFeatureName()
{
	if (!IsActive())
		return "Random Game Speed";

	return UTIL_VarArgs("Random Game Speed (%.02fx)", GetTimescale());
}

float CFeatureRandomGameSpeed::GetTimescale()
{
	return m_flGameSpeed;
}

double CFeatureRandomGameSpeed::GetDuration()
{
	return gChaos.GetChaosTime() * 0.5;
}