/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureViewOfsInsanity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREVIEWOFSINSANITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureViewOfsInsanity.h
#else //CFEATUREVIEWOFSINSANITY_H_RECURSE_GUARD

#define CFEATUREVIEWOFSINSANITY_H_RECURSE_GUARD

#ifndef CFEATUREVIEWOFSINSANITY_H_GUARD
#define CFEATUREVIEWOFSINSANITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureViewOfsInsanity : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void V_CalcRefdef(struct ref_params_s* pparams) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	Vector m_vecOldViewHeight;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureViewOfsInsanity.h
#endif //__cplusplus

#endif //CFEATUREVIEWOFSINSANITY_H_GUARD

#undef CFEATUREVIEWOFSINSANITY_H_RECURSE_GUARD
#endif //CFEATUREVIEWOFSINSANITY_H_RECURSE_GUARD