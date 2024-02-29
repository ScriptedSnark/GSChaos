/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGrieferShephard.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGRIEFERSHEPHARD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGrieferShephard.h
#else //CFEATUREGRIEFERSHEPHARD_H_RECURSE_GUARD

#define CFEATUREGRIEFERSHEPHARD_H_RECURSE_GUARD

#ifndef CFEATUREGRIEFERSHEPHARD_H_GUARD
#define CFEATUREGRIEFERSHEPHARD_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGrieferShephard : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void OnFrame(double time) override;
	void Spawn();
	void Think();
	void LaunchRocket();
private:
	double m_flRocketTime;
	edict_t* m_pShephard;
	bool m_bActivated;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGrieferShephard.h
#endif //__cplusplus

#endif //CFEATUREGRIEFERSHEPHARD_H_GUARD

#undef CFEATUREGRIEFERSHEPHARD_H_RECURSE_GUARD
#endif //CFEATUREGRIEFERSHEPHARD_H_RECURSE_GUARD