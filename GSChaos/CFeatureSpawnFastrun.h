/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureSpawnFastrun.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESPAWNFASTRUN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSpawnFastrun.h
#else //CFEATURESPAWNFASTRUN_H_RECURSE_GUARD

#define CFEATURESPAWNFASTRUN_H_RECURSE_GUARD

#ifndef CFEATURESPAWNFASTRUN_H_GUARD
#define CFEATURESPAWNFASTRUN_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSpawnFastrun : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
private:
	double m_flSpawnTime;
	bool m_bSpawned;
	edict_t* fastrun;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSpawnFastrun.h
#endif //__cplusplus

#endif //CFEATURESPAWNFASTRUN_H_GUARD

#undef CFEATURESPAWNFASTRUN_H_RECURSE_GUARD
#endif //CFEATURESPAWNFASTRUN_H_RECURSE_GUARD