/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureGTA2Camera.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGTA2CAMERA_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGTA2Camera.h
#else //CFEATUREGTA2CAMERA_H_RECURSE_GUARD

#define CFEATUREGTA2CAMERA_H_RECURSE_GUARD

#ifndef CFEATUREGTA2CAMERA_H_GUARD
#define CFEATUREGTA2CAMERA_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGTA2Camera : public CChaosFeature
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
	std::chrono::steady_clock::time_point m_lastFrameTime;
	bool m_bActivated;
	bool m_bAnimating;
	cvar_t* cl_pitchup, *cl_pitchdown;
	float cvar_values[5];
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGTA2Camera.h
#endif //__cplusplus

#endif //CFEATUREGTA2CAMERA_H_GUARD

#undef CFEATUREGTA2CAMERA_H_RECURSE_GUARD
#endif //CFEATUREGTA2CAMERA_H_RECURSE_GUARD