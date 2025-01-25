/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureScrollingHell.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESCROLLINGHELL_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureScrollingHell.h
#else //CFEATURESCROLLINGHELL_H_RECURSE_GUARD

#define CFEATURESCROLLINGHELL_H_RECURSE_GUARD

#ifndef CFEATURESCROLLINGHELL_H_GUARD
#define CFEATURESCROLLINGHELL_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureScrollingHell : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void R_DrawWorld() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureScrollingHell.h
#endif //__cplusplus

#endif //CFEATURESCROLLINGHELL_H_GUARD

#undef CFEATURESCROLLINGHELL_H_RECURSE_GUARD
#endif //CFEATURESCROLLINGHELL_H_RECURSE_GUARD