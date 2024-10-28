/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureExtremeGrieferJesus.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREEXTREMEGRIEFERJESUS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureExtremeGrieferJesus.h
#else //CFEATUREEXTREMEGRIEFERJESUS_H_RECURSE_GUARD

#define CFEATUREEXTREMEGRIEFERJESUS_H_RECURSE_GUARD

#ifndef CFEATUREEXTREMEGRIEFERJESUS_H_GUARD
#define CFEATUREEXTREMEGRIEFERJESUS_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bDespawnJesus;

class CFeatureExtremeGrieferJesus : public CFeatureExtremeGrieferShephard
{
	void ActivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	const char* GetModelName() override;
	const char* GetClassname() override;
	bool UseRenderFX() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	bool m_bActivated;
	double m_flTimeForSpawn;
	bool m_bMusicIsPlaying;
	double m_flMusicTime;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureExtremeGrieferJesus.h
#endif //__cplusplus

#endif //CFEATUREEXTREMEGRIEFERJESUS_H_GUARD

#undef CFEATUREEXTREMEGRIEFERJESUS_H_RECURSE_GUARD
#endif //CFEATUREEXTREMEGRIEFERJESUS_H_RECURSE_GUARD