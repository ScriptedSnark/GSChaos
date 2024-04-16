/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureQuakeJumpSound.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREQUAKEJUMPSOUND_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureQuakeJumpSound.h
#else //CFEATUREQUAKEJUMPSOUND_H_RECURSE_GUARD

#define CFEATUREQUAKEJUMPSOUND_H_RECURSE_GUARD

#ifndef CFEATUREQUAKEJUMPSOUND_H_GUARD
#define CFEATUREQUAKEJUMPSOUND_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureQuakeJumpSound : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void PM_Jump() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureQuakeJumpSound.h
#endif //__cplusplus

#endif //CFEATUREQUAKEJUMPSOUND_H_GUARD

#undef CFEATUREQUAKEJUMPSOUND_H_RECURSE_GUARD
#endif //CFEATUREQUAKEJUMPSOUND_H_RECURSE_GUARD