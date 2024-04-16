#include "includes.h"

bool g_bMLGAudio;
std::vector<std::string> g_szMLGSounds;

void CFeatureMLGAudio::ParseMLGDirectory()
{
	g_szMLGSounds.clear();

	try
	{
		for (const auto& entry : std::filesystem::directory_iterator("chaos\\mlg"))
		{
			if (entry.is_regular_file())
			{
				std::string fileName = entry.path().filename().string();
				if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".wav") // smh
				{
					g_szMLGSounds.push_back(fileName);
					DEBUG_PRINT("g_szMLGSounds: %s\n", fileName.c_str());
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error parsing MLG directory: " << e.what() << std::endl;
	}
}

void CFeatureMLGAudio::Init()
{
	CChaosFeature::Init();
	ParseMLGDirectory();
}

void CFeatureMLGAudio::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bMLGAudio = true;
}

void CFeatureMLGAudio::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bMLGAudio = false;
}

const char* CFeatureMLGAudio::GetFeatureName()
{
	return "MLG Audio";
}

double CFeatureMLGAudio::GetDuration()
{
	return gChaos.GetChaosTime() * 2.0;
}

bool CFeatureMLGAudio::UseCustomDuration()
{
	return true;
}