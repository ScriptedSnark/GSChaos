/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureEarthquake.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREEARTHQUAKE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureEarthquake.h
#else //CFEATUREEARTHQUAKE_H_RECURSE_GUARD

#define CFEATUREEARTHQUAKE_H_RECURSE_GUARD

#ifndef CFEATUREEARTHQUAKE_H_GUARD
#define CFEATUREEARTHQUAKE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureEarthquake : public CChaosFeature
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
#error C++ compiler required to compile CFeatureEarthquake.h
#endif //__cplusplus

#endif //CFEATUREEARTHQUAKE_H_GUARD

#undef CFEATUREEARTHQUAKE_H_RECURSE_GUARD
#endif //CFEATUREEARTHQUAKE_H_RECURSE_GUARD