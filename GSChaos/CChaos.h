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

class CChaos
{
public:
	void Init();
	void FeatureInit();
	void LoadFonts();
	void Reset();
	void Shutdown();
	void PrintVersion();
	void DrawBar();
	void DrawEffectList();
	void Draw();
	void OnFrame(double time);
	void ActivateChaosFeature(int i);
	int GetRandomValue(int min, int max);
	int GetRandomEffect(int min, int max);
	float GetRandomValue(float min, float max);
	double GetTime();
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
	int m_aiPreviousRandomValue[2];
	CTrustedRandom* m_lpRandomDevice;
	CChaosFeature* m_pCurrentFeature;
};

#else //!__cplusplus
#error C++ compiler required to compile CChaos.h
#endif //__cplusplus

#endif //CCHAOS_H_GUARD

#undef CCHAOS_H_RECURSE_GUARD
#endif //CCHAOS_H_RECURSE_GUARD