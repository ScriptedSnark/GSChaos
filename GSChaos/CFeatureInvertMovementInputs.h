/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureInvertMovementInputs.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREINVERTMOVEMENTINPUTS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureInvertMovementInputs.h
#else //CFEATUREINVERTMOVEMENTINPUTS_H_RECURSE_GUARD

#define CFEATUREINVERTMOVEMENTINPUTS_H_RECURSE_GUARD

#ifndef CFEATUREINVERTMOVEMENTINPUTS_H_GUARD
#define CFEATUREINVERTMOVEMENTINPUTS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureInvertMovementInputs : public CChaosFeature
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
#error C++ compiler required to compile CFeatureInvertMovementInputs.h
#endif //__cplusplus

#endif //CFEATUREINVERTMOVEMENTINPUTS_H_GUARD

#undef CFEATUREINVERTMOVEMENTINPUTS_H_RECURSE_GUARD
#endif //CFEATUREINVERTMOVEMENTINPUTS_H_RECURSE_GUARD