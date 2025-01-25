/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureDarkness.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREDARKNESS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureDarkness.h
#else //CFEATUREDARKNESS_H_RECURSE_GUARD

#define CFEATUREDARKNESS_H_RECURSE_GUARD

#ifndef CFEATUREDARKNESS_H_GUARD
#define CFEATUREDARKNESS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureDarkness : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void Restore() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureDarkness.h
#endif //__cplusplus

#endif //CFEATUREDARKNESS_H_GUARD

#undef CFEATUREDARKNESS_H_RECURSE_GUARD
#endif //CFEATUREDARKNESS_H_RECURSE_GUARD