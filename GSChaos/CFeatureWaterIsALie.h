/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureWaterIsALie.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREWATERISALIE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureWaterIsALie.h
#else //CFEATUREWATERISALIE_H_RECURSE_GUARD

#define CFEATUREWATERISALIE_H_RECURSE_GUARD

#ifndef CFEATUREWATERISALIE_H_GUARD
#define CFEATUREWATERISALIE_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedDisableWater;

class CFeatureWaterIsALie : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureWaterIsALie.h
#endif //__cplusplus

#endif //CFEATUREWATERISALIE_H_GUARD

#undef CFEATUREWATERISALIE_H_RECURSE_GUARD
#endif //CFEATUREWATERISALIE_H_RECURSE_GUARD