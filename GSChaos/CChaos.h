/**
 * Copyright - ScriptedSnark, 2024.
 * CChaos.h - chaos
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CCHAOS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CChaos.h
#else //CCHAOS_H_RECURSE_GUARD

#define CCHAOS_H_RECURSE_GUARD

#ifndef CCHAOS_H_GUARD
#define CCHAOS_H_GUARD
#pragma once

#ifdef __cplusplus

// Settings
#define CHAOS_ACTIVATE_TIMER 30.0
#define CHAOS_ADDITIONAL_TIME 15.0
#define CHAOS_TWITCH_SETTINGS_FILE "chaos/twitch.ini"

#define CHAOS_VOTING_PROGRESS_UPDATE_TIME 0.75
#define CHAOS_VOTING_PROGRESS_FILE "chaos/voting_progress.txt"

struct TwitchVoter
{
	std::string userName;
	int value;
};

extern cvar_t* chaos_dmca_safe;
extern cvar_t* chaos_draw_as_overlay;

class CChaos
{
public:
	void Init();
	bool LoadTwitchSettings();
	void InitVotingSystem();
	void FeatureInit();
	void LoadFonts();
	void VoteThink();
	void WriteVotingProgress();
	void StartVoting();
	void Vote(const std::string& user, const std::string& msg);
	int GetWinnerEffect();
	void Reset();
	void Shutdown();
	void PrintVersion();
	bool IsVoteStarted();
	void DrawBar();
	void DrawEffectList();
	void DrawVoting();
	void Draw();
	void ResetStates();
	void OnFrame(double time);
	void ActivateChaosFeature(int i);
	int GetRandomValue(int min, int max);
	int GetRandomEffect(int min, int max);
	float GetRandomValue(float min, float max);
	double GetTime();
	double GetChaosTime();
	double GetGlobalTime();
	int GetFrameCount();
	bool IsReady();

	ImFont* m_fontTrebuchet;
	ImFont* m_pArialBlack;
	ImFont* m_pArialBlackItalic;
	ImFont* m_pPricedown;
	ImFont* m_pArborcrest;

private:
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double, std::nano>> m_startTime;
	std::chrono::high_resolution_clock::time_point m_startGlobalTime;
	std::chrono::high_resolution_clock::time_point m_pauseStartTime; 
	std::chrono::duration<double> m_pauseOffset;
	std::random_device m_randDevice;
	ImVec2 m_chaosBarPos;
	bool m_bInitialized = false;
	bool m_bInGame = false;
	bool m_bPaused;
	float m_flProgress;
	double m_flChaosTime;
	double m_flTime;
	double m_flGlobalTime;
	int m_iFrameCount;
	int m_iBarColor[3];
	int m_iHackCounter;
	int m_aiPreviousRandomValue[3];
	CTrustedRandom* m_lpRandomDevice;
	CChaosFeature* m_pCurrentFeature;
	

	// TWITCH
	bool m_bTwitchVoting;
	bool m_bStartedVoting;
	int m_aiEffectsForVoting[3], m_aiVoteValues[3];
	int m_iWinnerEffect;
	std::string m_sUserName;
	std::string m_oAuth;
	std::vector<TwitchVoter> m_twitchVoters;
};

#else //!__cplusplus
#error C++ compiler required to compile CChaos.h
#endif //__cplusplus

#endif //CCHAOS_H_GUARD

#undef CCHAOS_H_RECURSE_GUARD
#endif //CCHAOS_H_RECURSE_GUARD