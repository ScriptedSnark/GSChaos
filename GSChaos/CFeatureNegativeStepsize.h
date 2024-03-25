/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureNegativeStepsize.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENEGATIVESTEPSIZE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNegativeStepsize.h
#else //CFEATURENEGATIVESTEPSIZE_H_RECURSE_GUARD

#define CFEATURENEGATIVESTEPSIZE_H_RECURSE_GUARD

#ifndef CFEATURENEGATIVESTEPSIZE_H_GUARD
#define CFEATURENEGATIVESTEPSIZE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNegativeStepsize : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;

	virtual float GetStepsizeValue();
private:
	bool m_bActivated;
	cvar_t* sv_stepsize;
	float m_flOldStepsizeValue;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNegativeStepsize.h
#endif //__cplusplus

#endif //CFEATURENEGATIVESTEPSIZE_H_GUARD

#undef CFEATURENEGATIVESTEPSIZE_H_RECURSE_GUARD
#endif //CFEATURENEGATIVESTEPSIZE_H_RECURSE_GUARD