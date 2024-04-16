/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureIceSkating.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREICESKATING_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureIceSkating.h
#else //CFEATUREICESKATING_H_RECURSE_GUARD

#define CFEATUREICESKATING_H_RECURSE_GUARD

#ifndef CFEATUREICESKATING_H_GUARD
#define CFEATUREICESKATING_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureIceSkating : public CChaosFeature
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
	cvar_t* sv_friction;
	float m_flOldFrictionValue;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureIceSkating.h
#endif //__cplusplus

#endif //CFEATUREICESKATING_H_GUARD

#undef CFEATUREICESKATING_H_RECURSE_GUARD
#endif //CFEATUREICESKATING_H_RECURSE_GUARD