#include "includes.h"

void CFeaturePortrait::Init()
{
	CChaosFeature::Init();
}

void CFeaturePortrait::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeaturePortrait::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeaturePortrait::Draw()
{
	if (!IsActive())
		return;
	
	float flWidth = ScreenWidth / 2 - UTIL_GetScreenCoord(300.0f);

	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(-1.0f, -1.0f), ImVec2(flWidth, ScreenHeight), IM_COL32(0, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(ScreenWidth - flWidth, -1.0f), ImVec2(ScreenWidth, ScreenHeight), IM_COL32(0, 0, 0, 255));
}

const char* CFeaturePortrait::GetFeatureName()
{
	return "Portrait Mode";
}

double CFeaturePortrait::GetDuration()
{
	return gChaos.GetChaosTime() * 1.1;
}

bool CFeaturePortrait::UseCustomDuration()
{
	return true;
}

bool CFeaturePortrait::CanBeInfinite()
{
	return true;
}