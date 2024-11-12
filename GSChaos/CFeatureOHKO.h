/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureOHKO.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREOHKO_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureOHKO.h
#else //CFEATUREOHKO_H_RECURSE_GUARD

#define CFEATUREOHKO_H_RECURSE_GUARD

#ifndef CFEATUREOHKO_H_GUARD
#define CFEATUREOHKO_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureOHKO : public CChaosFeature
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
#error C++ compiler required to compile CFeatureOHKO.h
#endif //__cplusplus

#endif //CFEATUREOHKO_H_GUARD

#undef CFEATUREOHKO_H_RECURSE_GUARD
#endif //CFEATUREOHKO_H_RECURSE_GUARD