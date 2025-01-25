/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureSleepy.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESLEEPY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSleepy.h
#else //CFEATURESLEEPY_H_RECURSE_GUARD

#define CFEATURESLEEPY_H_RECURSE_GUARD

#ifndef CFEATURESLEEPY_H_GUARD
#define CFEATURESLEEPY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSleepy : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
private:
	bool m_bActivated;
	double m_flSleepyTime;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSleepy.h
#endif //__cplusplus

#endif //CFEATURESLEEPY_H_GUARD

#undef CFEATURESLEEPY_H_RECURSE_GUARD
#endif //CFEATURESLEEPY_H_RECURSE_GUARD