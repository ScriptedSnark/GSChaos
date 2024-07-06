/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureKilometer.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREKILOMETER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureKilometer.h
#else //CFEATUREKILOMETER_H_RECURSE_GUARD

#define CFEATUREKILOMETER_H_RECURSE_GUARD

#ifndef CFEATUREKILOMETER_H_GUARD
#define CFEATUREKILOMETER_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedKilometer;

class CFeatureKilometer : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureKilometer.h
#endif //__cplusplus

#endif //CFEATUREKILOMETER_H_GUARD

#undef CFEATUREKILOMETER_H_RECURSE_GUARD
#endif //CFEATUREKILOMETER_H_RECURSE_GUARD