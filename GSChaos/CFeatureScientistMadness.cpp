#include "includes.h"

bool g_bScientistMadness;
std::vector<std::string> g_szSciSounds;

void CFeatureScientistMadness::Init()
{
	CChaosFeature::Init();

	g_szSciSounds.clear();

	try
	{
		for (const auto& entry : std::filesystem::directory_iterator("valve\\sound\\scientist"))
		{
			if (entry.is_regular_file())
			{
				std::string fileName = entry.path().filename().string();
				if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".wav") // smh
				{
					g_szSciSounds.push_back(fileName);
					DEBUG_PRINT("g_szSciSounds: %s\n", fileName.c_str());
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error parsing Scientist directory: " << e.what() << std::endl;
	}
}

void CFeatureScientistMadness::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bScientistMadness = true;
}

void CFeatureScientistMadness::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bScientistMadness = false;
}

const char* CFeatureScientistMadness::GetFeatureName()
{
	return "Scientist Madness";
}

double CFeatureScientistMadness::GetDuration()
{
	return gChaos.GetChaosTime() * 3.5;
}

bool CFeatureScientistMadness::UseCustomDuration()
{
	return true;
}