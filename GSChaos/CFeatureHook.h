/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureHook.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREHOOK_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureHook.h
#else //CFEATUREHOOK_H_RECURSE_GUARD

#define CFEATUREHOOK_H_RECURSE_GUARD

#ifndef CFEATUREHOOK_H_GUARD
#define CFEATUREHOOK_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureHook : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureHook.h
#endif //__cplusplus

#endif //CFEATUREHOOK_H_GUARD

#undef CFEATUREHOOK_H_RECURSE_GUARD
#endif //CFEATUREHOOK_H_RECURSE_GUARD