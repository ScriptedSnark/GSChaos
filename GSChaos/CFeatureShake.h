/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureShake.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESHAKE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureShake.h
#else //CFEATURESHAKE_H_RECURSE_GUARD

#define CFEATURESHAKE_H_RECURSE_GUARD

#ifndef CFEATURESHAKE_H_GUARD
#define CFEATURESHAKE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureShake : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureShake.h
#endif //__cplusplus

#endif //CFEATURESHAKE_H_GUARD

#undef CFEATURESHAKE_H_RECURSE_GUARD
#endif //CFEATURESHAKE_H_RECURSE_GUARD