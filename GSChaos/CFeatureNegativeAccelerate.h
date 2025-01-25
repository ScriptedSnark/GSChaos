/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureNegativeAccelerate.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENEGATIVEACCELERATE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNegativeAccelerate.h
#else //CFEATURENEGATIVEACCELERATE_H_RECURSE_GUARD

#define CFEATURENEGATIVEACCELERATE_H_RECURSE_GUARD

#ifndef CFEATURENEGATIVEACCELERATE_H_GUARD
#define CFEATURENEGATIVEACCELERATE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNegativeAccelerate : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
private:
	cvar_t* sv_accelerate;
	float m_flOldAccelerateValue;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNegativeAccelerate.h
#endif //__cplusplus

#endif //CFEATURENEGATIVEACCELERATE_H_GUARD

#undef CFEATURENEGATIVEACCELERATE_H_RECURSE_GUARD
#endif //CFEATURENEGATIVEACCELERATE_H_RECURSE_GUARD