/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureOverthinking.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREOVERTHINKING_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureOverthinking.h
#else //CFEATUREOVERTHINKING_H_RECURSE_GUARD

#define CFEATUREOVERTHINKING_H_RECURSE_GUARD

#ifndef CFEATUREOVERTHINKING_H_GUARD
#define CFEATUREOVERTHINKING_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureOverthinking : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureOverthinking.h
#endif //__cplusplus

#endif //CFEATUREOVERTHINKING_H_GUARD

#undef CFEATUREOVERTHINKING_H_RECURSE_GUARD
#endif //CFEATUREOVERTHINKING_H_RECURSE_GUARD