/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureTwitchy.h
 *
 * Project (GSChaos) header file
 * Authors: StereoBucket.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETWITCHY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTwitchy.h
#else //CFEATURETWITCHY_H_RECURSE_GUARD

#define CFEATURETWITCHY_H_RECURSE_GUARD

#ifndef CFEATURETWITCHY_H_GUARD
#define CFEATURETWITCHY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureTwitchy : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
private:
	double startshoot;
	double endshoot;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureTwitchy.h
#endif //__cplusplus

#endif //CFEATURETWITCHY_H_GUARD

#undef CFEATURETWITCHY_H_RECURSE_GUARD
#endif //CFEATURETWITCHY_H_RECURSE_GUARD