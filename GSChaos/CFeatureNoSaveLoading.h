/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureNoSaveLoading.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENOSAVELOADING_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNoSaveLoading.h
#else //CFEATURENOSAVELOADING_H_RECURSE_GUARD

#define CFEATURENOSAVELOADING_H_RECURSE_GUARD

#ifndef CFEATURENOSAVELOADING_H_GUARD
#define CFEATURENOSAVELOADING_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bNoLoad;

class CFeatureNoSaveLoading : public CChaosFeature
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
#error C++ compiler required to compile CFeatureNoSaveLoading.h
#endif //__cplusplus

#endif //CFEATURENOSAVELOADING_H_GUARD

#undef CFEATURENOSAVELOADING_H_RECURSE_GUARD
#endif //CFEATURENOSAVELOADING_H_RECURSE_GUARD