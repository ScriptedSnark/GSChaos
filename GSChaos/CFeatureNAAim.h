/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureNAAim.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENAAIM_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNAAim.h
#else //CFEATURENAAIM_H_RECURSE_GUARD

#define CFEATURENAAIM_H_RECURSE_GUARD

#ifndef CFEATURENAAIM_H_GUARD
#define CFEATURENAAIM_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNAAim : public CChaosFeature
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
#error C++ compiler required to compile CFeatureNAAim.h
#endif //__cplusplus

#endif //CFEATURENAAIM_H_GUARD

#undef CFEATURENAAIM_H_RECURSE_GUARD
#endif //CFEATURENAAIM_H_RECURSE_GUARD