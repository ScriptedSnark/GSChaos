/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeaturePunchangle.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREPUNCHANGLE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeaturePunchangle.h
#else //CFEATUREPUNCHANGLE_H_RECURSE_GUARD

#define CFEATUREPUNCHANGLE_H_RECURSE_GUARD

#ifndef CFEATUREPUNCHANGLE_H_GUARD
#define CFEATUREPUNCHANGLE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeaturePunchangle : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeaturePunchangle.h
#endif //__cplusplus

#endif //CFEATUREPUNCHANGLE_H_GUARD

#undef CFEATUREPUNCHANGLE_H_RECURSE_GUARD
#endif //CFEATUREPUNCHANGLE_H_RECURSE_GUARD