/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureFloatingPointInaccuracy.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREFLOATINGPOINTINACCURACY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureFloatingPointInaccuracy.h
#else //CFEATUREFLOATINGPOINTINACCURACY_H_RECURSE_GUARD

#define CFEATUREFLOATINGPOINTINACCURACY_H_RECURSE_GUARD

#ifndef CFEATUREFLOATINGPOINTINACCURACY_H_GUARD
#define CFEATUREFLOATINGPOINTINACCURACY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureFloatingPointInaccuracy : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void PM_Move(struct playermove_s* ppmove, qboolean server) override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override { return true; };
private:
	double m_flNextThink;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureFloatingPointInaccuracy.h
#endif //__cplusplus

#endif //CFEATUREFLOATINGPOINTINACCURACY_H_GUARD

#undef CFEATUREFLOATINGPOINTINACCURACY_H_RECURSE_GUARD
#endif //CFEATUREFLOATINGPOINTINACCURACY_H_RECURSE_GUARD