#include "includes.h"

bool g_bHEVMadness = false;

std::vector<const char*> g_szHEVSentences =
{
	"E",
	"DET",
	"HEAL",
	"DEAD"
};

void CFeatureHEVMadness::Init()
{
	CChaosFeature::Init();
}

void CFeatureHEVMadness::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bHEVMadness = true;
}

void CFeatureHEVMadness::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bHEVMadness = false;
}

const char* CFeatureHEVMadness::GetFeatureName()
{
	return "HEV Madness";
}

double CFeatureHEVMadness::GetDuration()
{
	return gChaos.GetChaosTime() * 1.15;
}

bool CFeatureHEVMadness::UseCustomDuration()
{
	return true;
}