#include "includes.h"

bool g_bHEVMadness = false;

std::vector<std::string> g_szHEVSounds;

void CFeatureHEVMadness::Init()
{
	CChaosFeature::Init();

	g_szHEVSounds.clear();

	try
	{
#ifdef COF_BUILD
		for (const auto& entry : std::filesystem::directory_iterator("cryoffear\\sound\\subtitles"))
#else
		for (const auto& entry : std::filesystem::directory_iterator("valve\\sound\\fvox"))
#endif
		{
			if (entry.is_regular_file())
			{
				std::string fileName = entry.path().filename().string();
				if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".wav") // smh
				{
					g_szHEVSounds.push_back(fileName);
					DEBUG_PRINT("g_szHEVSounds: %s\n", fileName.c_str());
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error parsing HEV directory: " << e.what() << std::endl;
	}
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
#ifdef COF_BUILD
	return "VOICES IN YOUR HEAD";
#else
	return "HEV Madness";
#endif
}

double CFeatureHEVMadness::GetDuration()
{
	return gChaos.GetChaosTime() * 1.15;
}

bool CFeatureHEVMadness::UseCustomDuration()
{
	return true;
}

bool CFeatureHEVMadness::CanBeInfinite()
{
	return true;
}