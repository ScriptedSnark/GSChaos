/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureNotarget.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENOTARGET_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNotarget.h
#else //CFEATURENOTARGET_H_RECURSE_GUARD

#define CFEATURENOTARGET_H_RECURSE_GUARD

#ifndef CFEATURENOTARGET_H_GUARD
#define CFEATURENOTARGET_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNotarget : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	void ResetStates() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool IsGood() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNotarget.h
#endif //__cplusplus

#endif //CFEATURENOTARGET_H_GUARD

#undef CFEATURENOTARGET_H_RECURSE_GUARD
#endif //CFEATURENOTARGET_H_RECURSE_GUARD