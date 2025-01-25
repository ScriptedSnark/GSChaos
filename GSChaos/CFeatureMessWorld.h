/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureMessWorld.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMESSWORLD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMessWorld.h
#else //CFEATUREMESSWORLD_H_RECURSE_GUARD

#define CFEATUREMESSWORLD_H_RECURSE_GUARD

#ifndef CFEATUREMESSWORLD_H_GUARD
#define CFEATUREMESSWORLD_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bBrokenTextures;

class CFeatureMessWorld : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	void MessTextures();
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
private:
	double m_flMessTime;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureMessWorld.h
#endif //__cplusplus

#endif //CFEATUREMESSWORLD_H_GUARD

#undef CFEATUREMESSWORLD_H_RECURSE_GUARD
#endif //CFEATUREMESSWORLD_H_RECURSE_GUARD