/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureHalfGameSpeed.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREHALFGAMESPEED_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureHalfGameSpeed.h
#else //CFEATUREHALFGAMESPEED_H_RECURSE_GUARD

#define CFEATUREHALFGAMESPEED_H_RECURSE_GUARD

#ifndef CFEATUREHALFGAMESPEED_H_GUARD
#define CFEATUREHALFGAMESPEED_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureHalfGameSpeed : public CChaosFeature
{
public:
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	virtual float GetTimescale();
	bool CanBeInfinite() override { return true; };
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureHalfGameSpeed.h
#endif //__cplusplus

#endif //CFEATUREHALFGAMESPEED_H_GUARD

#undef CFEATUREHALFGAMESPEED_H_RECURSE_GUARD
#endif //CFEATUREHALFGAMESPEED_H_RECURSE_GUARD