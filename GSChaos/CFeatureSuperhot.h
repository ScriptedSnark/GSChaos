/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureSuperhot.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESUPERHOT_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSuperhot.h
#else //CFEATURESUPERHOT_H_RECURSE_GUARD

#define CFEATURESUPERHOT_H_RECURSE_GUARD

#ifndef CFEATURESUPERHOT_H_GUARD
#define CFEATURESUPERHOT_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSuperhot : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSuperhot.h
#endif //__cplusplus

#endif //CFEATURESUPERHOT_H_GUARD

#undef CFEATURESUPERHOT_H_RECURSE_GUARD
#endif //CFEATURESUPERHOT_H_RECURSE_GUARD