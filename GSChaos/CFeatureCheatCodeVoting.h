/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureCheatCodeVoting.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURECHEATCODEVOTING_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureCheatCodeVoting.h
#else //CFEATURECHEATCODEVOTING_H_RECURSE_GUARD

#define CFEATURECHEATCODEVOTING_H_RECURSE_GUARD

#ifndef CFEATURECHEATCODEVOTING_H_GUARD
#define CFEATURECHEATCODEVOTING_H_GUARD
#pragma once

#ifdef __cplusplus

struct VotedFeature
{
	CChaosFeature* feature;
	std::string user;
};

extern std::vector<CChaosFeature*> g_pCheatCodeFeatures;

class CFeatureCheatCodeVoting : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	void Vote(const std::string& user, const std::string& msg);
private:
	std::vector<TwitchVoter> m_twitchVoters;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureCheatCodeVoting.h
#endif //__cplusplus

#endif //CFEATURECHEATCODEVOTING_H_GUARD

#undef CFEATURECHEATCODEVOTING_H_RECURSE_GUARD
#endif //CFEATURECHEATCODEVOTING_H_RECURSE_GUARD