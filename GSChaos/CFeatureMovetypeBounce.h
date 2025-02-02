/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureMovetypeBounce.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMOVETYPEBOUNCE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMovetypeBounce.h
#else //CFEATUREMOVETYPEBOUNCE_H_RECURSE_GUARD

#define CFEATUREMOVETYPEBOUNCE_H_RECURSE_GUARD

#ifndef CFEATUREMOVETYPEBOUNCE_H_GUARD
#define CFEATUREMOVETYPEBOUNCE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureMovetypeBounce : public CChaosFeature
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
#error C++ compiler required to compile CFeatureMovetypeBounce.h
#endif //__cplusplus

#endif //CFEATUREMOVETYPEBOUNCE_H_GUARD

#undef CFEATUREMOVETYPEBOUNCE_H_RECURSE_GUARD
#endif //CFEATUREMOVETYPEBOUNCE_H_RECURSE_GUARD