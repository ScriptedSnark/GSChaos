#include "twitch/twitch.h"
#include "includes.h"

bool g_bActivatedCheatCodeVoting = false;
extern Twitch* twitch;

std::unordered_map<std::string, std::string> g_featureAliases =
{
	{ "SpawnExtremeGrieferJesus", "He comes back." },
	//...
};

void CFeatureCheatCodeVoting::Init()
{
	CChaosFeature::Init();
}

void CFeatureCheatCodeVoting::Vote(const std::string& user, const std::string& msg)
{
	if (!gChaos.m_bTwitchVoting)
		return;

	if (!IsActive())
		return;

	auto it = std::find_if(m_twitchVoters.begin(), m_twitchVoters.end(), [&](const TwitchVoter& voter) {
		return voter.userName == user;
		});

	if (it != m_twitchVoters.end())
	{
		DEBUG_PRINT("Twitch user %s has already voted.\n", user.c_str());
		return;
	}

	std::string featureName = msg;
	auto aliasIt = g_featureAliases.find(msg);

	if (aliasIt != g_featureAliases.end())
		featureName = aliasIt->second;

	auto featureIt = std::find_if(gChaosFeaturesNames.begin(), gChaosFeaturesNames.end(), [&](const char* name) {
		return strstr(featureName.c_str(), name);
		});

	if (strstr(featureName.c_str(), GetFeatureName()))
	{
		twitch->SendChatMessage("\"Cheat Code Voting\" effect is unavailable.");
		return;
	}

	if (featureIt != gChaosFeaturesNames.end())
	{
		auto featureIndex = std::distance(gChaosFeaturesNames.begin(), featureIt);
		if (featureIndex >= 0 && featureIndex < gChaosFeatures.size())
		{
			CChaosFeature* feature = gChaosFeatures[featureIndex];

			auto featureInList = std::find(m_pFeatures.begin(), m_pFeatures.end(), feature);
			if (featureInList == m_pFeatures.end())
			{
				feature->SetVoterNickname(user);
				m_twitchVoters.push_back({ user, 0 }); // were lazy for another struct =_)
				m_pFeatures.push_back(feature);
				DEBUG_PRINT("Twitch user %s voted for feature: %s\n", user.c_str(), featureName.c_str());
			}
			else
			{
				DEBUG_PRINT("Feature \"%s\" is already in vote list.\n", featureName.c_str());
			}
		}
		else
		{
			DEBUG_PRINT("Invalid feature index for user %s: %d\n", user.c_str(), featureIndex);
		}
	}
	else
	{
		DEBUG_PRINT("Twitch user %s voted for an unknown feature: %s\n", user.c_str(), featureName.c_str());
	}
}

void CFeatureCheatCodeVoting::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	if (!gChaos.m_bTwitchVoting)
	{
		gChaosFeatures[gChaos.GetRandomValue(1, 100)]->ActivateFeature();
		CChaosFeature::DeactivateFeature();
	}

	if (twitch)
		twitch->SendChatMessage("Start writing wanted effects names!");

	m_twitchVoters.clear();
	m_pFeatures.clear();

	g_bActivatedCheatCodeVoting = true;
}

void CFeatureCheatCodeVoting::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	g_bActivatedCheatCodeVoting = false;

	for (auto& i : m_pFeatures)
	{
		i->ActivateFeature();
	}
}

const char* CFeatureCheatCodeVoting::GetFeatureName()
{
	return "Cheat Code Voting";
}

double CFeatureCheatCodeVoting::GetDuration()
{
	return 10.0;
}

bool CFeatureCheatCodeVoting::UseCustomDuration()
{
	return true;
}