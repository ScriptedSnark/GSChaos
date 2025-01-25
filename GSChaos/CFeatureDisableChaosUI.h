/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureDisableChaosUI.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREDISABLECHAOSUI_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureDisableChaosUI.h
#else //CFEATUREDISABLECHAOSUI_H_RECURSE_GUARD

#define CFEATUREDISABLECHAOSUI_H_RECURSE_GUARD

#ifndef CFEATUREDISABLECHAOSUI_H_GUARD
#define CFEATUREDISABLECHAOSUI_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureDisableChaosUI : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureDisableChaosUI.h
#endif //__cplusplus

#endif //CFEATUREDISABLECHAOSUI_H_GUARD

#undef CFEATUREDISABLECHAOSUI_H_RECURSE_GUARD
#endif //CFEATUREDISABLECHAOSUI_H_RECURSE_GUARD