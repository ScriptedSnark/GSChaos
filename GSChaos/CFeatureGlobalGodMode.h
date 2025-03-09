/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureGlobalGodMode.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGLOBALGODMODE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGlobalGodMode.h
#else //CFEATUREGLOBALGODMODE_H_RECURSE_GUARD

#define CFEATUREGLOBALGODMODE_H_RECURSE_GUARD

#ifndef CFEATUREGLOBALGODMODE_H_GUARD
#define CFEATUREGLOBALGODMODE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGlobalGodMode : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override { return true; };

private:
	bool m_bActivated = false;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGlobalGodMode.h
#endif //__cplusplus

#endif //CFEATUREGLOBALGODMODE_H_GUARD

#undef CFEATUREGLOBALGODMODE_H_RECURSE_GUARD
#endif //CFEATUREGLOBALGODMODE_H_RECURSE_GUARD