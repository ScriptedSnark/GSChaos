/**
 * Copyright - ScriptedSnark, 2024.
 * CFeaturePortrait.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREPORTRAIT_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeaturePortrait.h
#else //CFEATUREPORTRAIT_H_RECURSE_GUARD

#define CFEATUREPORTRAIT_H_RECURSE_GUARD

#ifndef CFEATUREPORTRAIT_H_GUARD
#define CFEATUREPORTRAIT_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeaturePortrait : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void Draw() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeaturePortrait.h
#endif //__cplusplus

#endif //CFEATUREPORTRAIT_H_GUARD

#undef CFEATUREPORTRAIT_H_RECURSE_GUARD
#endif //CFEATUREPORTRAIT_H_RECURSE_GUARD