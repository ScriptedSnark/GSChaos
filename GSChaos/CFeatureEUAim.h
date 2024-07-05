/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureEUAim.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREEUAIM_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureEUAim.h
#else //CFEATUREEUAIM_H_RECURSE_GUARD

#define CFEATUREEUAIM_H_RECURSE_GUARD

#ifndef CFEATUREEUAIM_H_GUARD
#define CFEATUREEUAIM_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureEUAim : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureEUAim.h
#endif //__cplusplus

#endif //CFEATUREEUAIM_H_GUARD

#undef CFEATUREEUAIM_H_RECURSE_GUARD
#endif //CFEATUREEUAIM_H_RECURSE_GUARD