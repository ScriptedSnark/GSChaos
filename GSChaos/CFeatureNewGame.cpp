#include "includes.h"

void CFeatureNewGame::Init()
{
	CChaosFeature::Init();

	std::string path = std::string(pEngfuncs->pfnGetGameDirectory()) + '\\' + "liblist.gam"; // I hate this so much
	std::ifstream file(path);

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string key, value;
		if (std::getline(iss, key, ' ') && std::getline(iss, value))
		{
			if (key == "startmap")
			{
				m_sMapName = value;
				break;
			}
		}
	}

	file.close();

	DEBUG_PRINT("[NEW GAME] Start map: %s\n", m_sMapName.c_str());
}

void CFeatureNewGame::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	if (m_sMapName.empty())
	{
		CChaosFeature::DeactivateFeature();
		return;
	}

	pEngfuncs->pfnClientCmd(UTIL_VarArgs(";map %s;\n", m_sMapName.c_str()));
}

void CFeatureNewGame::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureNewGame::GetFeatureName()
{
	return "New Game :tf:";
}