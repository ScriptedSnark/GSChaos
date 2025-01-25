#include "includes.h"

void CFeaturePunchangle::Init()
{
	CChaosFeature::Init();
}

void CFeaturePunchangle::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeaturePunchangle::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeaturePunchangle::OnFrame(double time)
{
	if (!IsActive())
		return;
	
	if ((*sv_player)->v.punchangle.Length() < 15.0f)
	{
		(*sv_player)->v.punchangle.y = 720.0f;
		(*sv_player)->v.punchangle.z = 720.0f;
	}
}

const char* CFeaturePunchangle::GetFeatureName()
{
	return "Dizziness";
}

double CFeaturePunchangle::GetDuration()
{
	return gChaos.GetChaosTime() * 0.55;
}

bool CFeaturePunchangle::UseCustomDuration()
{
	return true;
}

bool CFeaturePunchangle::CanBeInfinite()
{
	return true;
}