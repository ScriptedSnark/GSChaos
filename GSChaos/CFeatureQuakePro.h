/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureQuakePro.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREQUAKEPRO_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureQuakePro.h
#else //CFEATUREQUAKEPRO_H_RECURSE_GUARD

#define CFEATUREQUAKEPRO_H_RECURSE_GUARD

#ifndef CFEATUREQUAKEPRO_H_GUARD
#define CFEATUREQUAKEPRO_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureQuakePro : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
public:
	virtual float GetFOV();
private:
	cvar_t* default_fov;
	float m_flOldFOVValue;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureQuakePro.h
#endif //__cplusplus

#endif //CFEATUREQUAKEPRO_H_GUARD

#undef CFEATUREQUAKEPRO_H_RECURSE_GUARD
#endif //CFEATUREQUAKEPRO_H_RECURSE_GUARD