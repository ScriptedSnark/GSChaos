/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureEntitySpin.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREENTITYSPIN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureEntitySpin.h
#else //CFEATUREENTITYSPIN_H_RECURSE_GUARD

#define CFEATUREENTITYSPIN_H_RECURSE_GUARD

#ifndef CFEATUREENTITYSPIN_H_GUARD
#define CFEATUREENTITYSPIN_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureEntitySpin : public CChaosFeature
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
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureEntitySpin.h
#endif //__cplusplus

#endif //CFEATUREENTITYSPIN_H_GUARD

#undef CFEATUREENTITYSPIN_H_RECURSE_GUARD
#endif //CFEATUREENTITYSPIN_H_RECURSE_GUARD