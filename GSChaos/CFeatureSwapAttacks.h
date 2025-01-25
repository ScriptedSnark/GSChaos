/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureSwapAttacks.h
 *
 * Project (GSChaos) header file
 * Authors: StereoBucket.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESWAPATTACKS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSwapAttacks.h
#else //CFEATURESWAPATTACKS_H_RECURSE_GUARD

#define CFEATURESWAPATTACKS_H_RECURSE_GUARD

#ifndef CFEATURESWAPATTACKS_H_GUARD
#define CFEATURESWAPATTACKS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSwapAttacks : public CChaosFeature
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
#error C++ compiler required to compile CFeatureSwapAttacks.h
#endif //__cplusplus

#endif //CFEATURESWAPATTACKS_H_GUARD

#undef CFEATURESWAPATTACKS_H_RECURSE_GUARD
#endif //CFEATURESWAPATTACKS_H_RECURSE_GUARD