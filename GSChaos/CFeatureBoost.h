/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureBoost.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREBOOST_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureBoost.h
#else //CFEATUREBOOST_H_RECURSE_GUARD

#define CFEATUREBOOST_H_RECURSE_GUARD

#ifndef CFEATUREBOOST_H_GUARD
#define CFEATUREBOOST_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureBoost : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureBoost.h
#endif //__cplusplus

#endif //CFEATUREBOOST_H_GUARD

#undef CFEATUREBOOST_H_RECURSE_GUARD
#endif //CFEATUREBOOST_H_RECURSE_GUARD