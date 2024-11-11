/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureVoidclip.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREVOIDCLIP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureVoidclip.h
#else //CFEATUREVOIDCLIP_H_RECURSE_GUARD

#define CFEATUREVOIDCLIP_H_RECURSE_GUARD

#ifndef CFEATUREVOIDCLIP_H_GUARD
#define CFEATUREVOIDCLIP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureVoidclip : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	float m_flNextTeleportTime;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureVoidclip.h
#endif //__cplusplus

#endif //CFEATUREVOIDCLIP_H_GUARD

#undef CFEATUREVOIDCLIP_H_RECURSE_GUARD
#endif //CFEATUREVOIDCLIP_H_RECURSE_GUARD