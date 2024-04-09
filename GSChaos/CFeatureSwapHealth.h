/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureSwapHealth.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESWAPHEALTH_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSwapHealth.h
#else //CFEATURESWAPHEALTH_H_RECURSE_GUARD

#define CFEATURESWAPHEALTH_H_RECURSE_GUARD

#ifndef CFEATURESWAPHEALTH_H_GUARD
#define CFEATURESWAPHEALTH_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSwapHealth : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSwapHealth.h
#endif //__cplusplus

#endif //CFEATURESWAPHEALTH_H_GUARD

#undef CFEATURESWAPHEALTH_H_RECURSE_GUARD
#endif //CFEATURESWAPHEALTH_H_RECURSE_GUARD