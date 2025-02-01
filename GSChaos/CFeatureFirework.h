/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureFirework.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark, Sanji (AMXX script - AMX Fireworks 1.2.3).
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREFIREWORK_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureFirework.h
#else //CFEATUREFIREWORK_H_RECURSE_GUARD

#define CFEATUREFIREWORK_H_RECURSE_GUARD

#ifndef CFEATUREFIREWORK_H_GUARD
#define CFEATUREFIREWORK_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureFirework : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
	void Restore() override;

private:
	void FireworksThink();
	void ShooterThink();
	void Explode(edict_t* pEdict);
	void CreateFirework(Vector origin, Vector angles, int r, int g, int b);

	int m_iSprSmoke;
	int m_iSprFlare6;
	int m_iSprLgtning;
	int m_iSndFirework;

	float m_flNextFireworkTime;
	float m_flNextShooterTime;

	std::vector<edict_t*> m_vFireworks;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureFirework.h
#endif //__cplusplus

#endif //CFEATUREFIREWORK_H_GUARD

#undef CFEATUREFIREWORK_H_RECURSE_GUARD
#endif //CFEATUREFIREWORK_H_RECURSE_GUARD