/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureHEVMadness.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREHEVMADNESS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureHEVMadness.h
#else //CFEATUREHEVMADNESS_H_RECURSE_GUARD

#define CFEATUREHEVMADNESS_H_RECURSE_GUARD

#ifndef CFEATUREHEVMADNESS_H_GUARD
#define CFEATUREHEVMADNESS_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bHEVMadness;
extern std::vector<std::string> g_szHEVSounds;

class CFeatureHEVMadness : public CChaosFeature
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
#error C++ compiler required to compile CFeatureHEVMadness.h
#endif //__cplusplus

#endif //CFEATUREHEVMADNESS_H_GUARD

#undef CFEATUREHEVMADNESS_H_RECURSE_GUARD
#endif //CFEATUREHEVMADNESS_H_RECURSE_GUARD