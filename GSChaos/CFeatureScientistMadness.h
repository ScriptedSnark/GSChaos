/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureScientistMadness.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESCIENTISTMADNESS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureScientistMadness.h
#else //CFEATURESCIENTISTMADNESS_H_RECURSE_GUARD

#define CFEATURESCIENTISTMADNESS_H_RECURSE_GUARD

#ifndef CFEATURESCIENTISTMADNESS_H_GUARD
#define CFEATURESCIENTISTMADNESS_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bScientistMadness;
extern std::vector<std::string> g_szSciSounds;

class CFeatureScientistMadness : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureScientistMadness.h
#endif //__cplusplus

#endif //CFEATURESCIENTISTMADNESS_H_GUARD

#undef CFEATURESCIENTISTMADNESS_H_RECURSE_GUARD
#endif //CFEATURESCIENTISTMADNESS_H_RECURSE_GUARD