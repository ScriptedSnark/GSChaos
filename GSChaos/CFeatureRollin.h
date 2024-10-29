/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureRollin.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREROLLIN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureRollin.h
#else //CFEATUREROLLIN_H_RECURSE_GUARD

#define CFEATUREROLLIN_H_RECURSE_GUARD

#ifndef CFEATUREROLLIN_H_GUARD
#define CFEATUREROLLIN_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedRollin;

class CFeatureRollin : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void V_CalcRefdef(struct ref_params_s* pparams) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureRollin.h
#endif //__cplusplus

#endif //CFEATUREROLLIN_H_GUARD

#undef CFEATUREROLLIN_H_RECURSE_GUARD
#endif //CFEATUREROLLIN_H_RECURSE_GUARD