/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureArmorSpeedometer.h - KreedZ reference
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREARMORSPEEDOMETER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureArmorSpeedometer.h
#else //CFEATUREARMORSPEEDOMETER_H_RECURSE_GUARD

#define CFEATUREARMORSPEEDOMETER_H_RECURSE_GUARD

#ifndef CFEATUREARMORSPEEDOMETER_H_GUARD
#define CFEATUREARMORSPEEDOMETER_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureArmorSpeedometer : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureArmorSpeedometer.h
#endif //__cplusplus

#endif //CFEATUREARMORSPEEDOMETER_H_GUARD

#undef CFEATUREARMORSPEEDOMETER_H_RECURSE_GUARD
#endif //CFEATUREARMORSPEEDOMETER_H_RECURSE_GUARD