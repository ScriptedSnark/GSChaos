/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureExtremeGrieferShephard.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREEXTREMEGRIEFERSHEPHARD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureExtremeGrieferShephard.h
#else //CFEATUREEXTREMEGRIEFERSHEPHARD_H_RECURSE_GUARD

#define CFEATUREEXTREMEGRIEFERSHEPHARD_H_RECURSE_GUARD

#ifndef CFEATUREEXTREMEGRIEFERSHEPHARD_H_GUARD
#define CFEATUREEXTREMEGRIEFERSHEPHARD_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bDespawnExShephard;

class CFeatureExtremeGrieferShephard : public CFeatureGrieferShephard
{
public:
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void OnFrame(double time) override;
	void Spawn() override;
	void Think() override;
	void LaunchRocket() override;
	void Restore() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	virtual const char* GetModelName();
	virtual const char* GetClassname();
	virtual bool UseRenderFX();

	bool m_bSpawned;
	double m_flDespawnTime;
private:
	double m_flRocketTime;
	edict_t* m_pShephard;
	Vector m_shephardLatestOrigin;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureExtremeGrieferShephard.h
#endif //__cplusplus

#endif //CFEATUREEXTREMEGRIEFERSHEPHARD_H_GUARD

#undef CFEATUREEXTREMEGRIEFERSHEPHARD_H_RECURSE_GUARD
#endif //CFEATUREEXTREMEGRIEFERSHEPHARD_H_RECURSE_GUARD