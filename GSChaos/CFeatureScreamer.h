/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureScreamer.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESCREAMER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureScreamer.h
#else //CFEATURESCREAMER_H_RECURSE_GUARD

#define CFEATURESCREAMER_H_RECURSE_GUARD

#ifndef CFEATURESCREAMER_H_GUARD
#define CFEATURESCREAMER_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureScreamer : public CChaosFeature
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
#error C++ compiler required to compile CFeatureScreamer.h
#endif //__cplusplus

#endif //CFEATURESCREAMER_H_GUARD

#undef CFEATURESCREAMER_H_RECURSE_GUARD
#endif //CFEATURESCREAMER_H_RECURSE_GUARD