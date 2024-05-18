#include "includes.h"

bool g_bActivatedMirror;

void CFeatureMirrorScreen::Init()
{
	CChaosFeature::Init();
}

void CFeatureMirrorScreen::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedMirror = true;
}

void CFeatureMirrorScreen::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedMirror = false;
}

const char* CFeatureMirrorScreen::GetFeatureName()
{
	return "rorriM";
}

double CFeatureMirrorScreen::GetDuration()
{
	return gChaos.GetChaosTime() * 1.08;
}

bool CFeatureMirrorScreen::UseCustomDuration()
{
	return true;
}