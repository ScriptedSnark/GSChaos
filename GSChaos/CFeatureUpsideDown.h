/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureUpsideDown.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREUPSIDEDOWN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureUpsideDown.h
#else //CFEATUREUPSIDEDOWN_H_RECURSE_GUARD

#define CFEATUREUPSIDEDOWN_H_RECURSE_GUARD

#ifndef CFEATUREUPSIDEDOWN_H_GUARD
#define CFEATUREUPSIDEDOWN_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureUpsideDown : public CChaosFeature
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
#error C++ compiler required to compile CFeatureUpsideDown.h
#endif //__cplusplus

#endif //CFEATUREUPSIDEDOWN_H_GUARD

#undef CFEATUREUPSIDEDOWN_H_RECURSE_GUARD
#endif //CFEATUREUPSIDEDOWN_H_RECURSE_GUARD