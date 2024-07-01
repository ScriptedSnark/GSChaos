/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureViewDistortion.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREVIEWDISTORTION_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureViewDistortion.h
#else //CFEATUREVIEWDISTORTION_H_RECURSE_GUARD

#define CFEATUREVIEWDISTORTION_H_RECURSE_GUARD

#ifndef CFEATUREVIEWDISTORTION_H_GUARD
#define CFEATUREVIEWDISTORTION_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedViewDistortion;

class CFeatureViewDistortion : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureViewDistortion.h
#endif //__cplusplus

#endif //CFEATUREVIEWDISTORTION_H_GUARD

#undef CFEATUREVIEWDISTORTION_H_RECURSE_GUARD
#endif //CFEATUREVIEWDISTORTION_H_RECURSE_GUARD