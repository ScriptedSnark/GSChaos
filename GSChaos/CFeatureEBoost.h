/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureEBoost.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREEBOOST_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureEBoost.h
#else //CFEATUREEBOOST_H_RECURSE_GUARD

#define CFEATUREEBOOST_H_RECURSE_GUARD

#ifndef CFEATUREEBOOST_H_GUARD
#define CFEATUREEBOOST_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureEBoost : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureEBoost.h
#endif //__cplusplus

#endif //CFEATUREEBOOST_H_GUARD

#undef CFEATUREEBOOST_H_RECURSE_GUARD
#endif //CFEATUREEBOOST_H_RECURSE_GUARD