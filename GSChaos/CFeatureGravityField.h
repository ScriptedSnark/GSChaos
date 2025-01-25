/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureGravityField.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGRAVITYFIELD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGravityField.h
#else //CFEATUREGRAVITYFIELD_H_RECURSE_GUARD

#define CFEATUREGRAVITYFIELD_H_RECURSE_GUARD

#ifndef CFEATUREGRAVITYFIELD_H_GUARD
#define CFEATUREGRAVITYFIELD_H_GUARD
#pragma once

#ifdef __cplusplus

#define MAGNET_SPEED 1500.0f

class CFeatureGravityField : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	bool m_bActivated;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGravityField.h
#endif //__cplusplus

#endif //CFEATUREGRAVITYFIELD_H_GUARD

#undef CFEATUREGRAVITYFIELD_H_RECURSE_GUARD
#endif //CFEATUREGRAVITYFIELD_H_RECURSE_GUARD