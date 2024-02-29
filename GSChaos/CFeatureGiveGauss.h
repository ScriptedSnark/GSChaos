/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGiveGauss.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGIVEGAUSS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGiveGauss.h
#else //CFEATUREGIVEGAUSS_H_RECURSE_GUARD

#define CFEATUREGIVEGAUSS_H_RECURSE_GUARD

#ifndef CFEATUREGIVEGAUSS_H_GUARD
#define CFEATUREGIVEGAUSS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGiveGauss : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGiveGauss.h
#endif //__cplusplus

#endif //CFEATUREGIVEGAUSS_H_GUARD

#undef CFEATUREGIVEGAUSS_H_RECURSE_GUARD
#endif //CFEATUREGIVEGAUSS_H_RECURSE_GUARD