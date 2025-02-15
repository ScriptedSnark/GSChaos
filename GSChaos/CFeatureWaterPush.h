/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureWaterPush.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREWATERPUSH_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureWaterPush.h
#else //CFEATUREWATERPUSH_H_RECURSE_GUARD

#define CFEATUREWATERPUSH_H_RECURSE_GUARD

#ifndef CFEATUREWATERPUSH_H_GUARD
#define CFEATUREWATERPUSH_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureWaterPush : public CChaosFeature
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
#error C++ compiler required to compile CFeatureWaterPush.h
#endif //__cplusplus

#endif //CFEATUREWATERPUSH_H_GUARD

#undef CFEATUREWATERPUSH_H_RECURSE_GUARD
#endif //CFEATUREWATERPUSH_H_RECURSE_GUARD