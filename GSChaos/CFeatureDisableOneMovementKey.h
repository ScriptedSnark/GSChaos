/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureDisableOneMovementKey.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREDISABLEONEMOVEMENTKEY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureDisableOneMovementKey.h
#else //CFEATUREDISABLEONEMOVEMENTKEY_H_RECURSE_GUARD

#define CFEATUREDISABLEONEMOVEMENTKEY_H_RECURSE_GUARD

#ifndef CFEATUREDISABLEONEMOVEMENTKEY_H_GUARD
#define CFEATUREDISABLEONEMOVEMENTKEY_H_GUARD
#pragma once

#ifdef __cplusplus

enum
{
	KEY_FORWARD = 0,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_BACK,
	MAX_KEYS
};

class CFeatureDisableOneMovementKey : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
	const char* GetKeyName();
private:
	bool m_bDisabledMovementKeys[MAX_KEYS];
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureDisableOneMovementKey.h
#endif //__cplusplus

#endif //CFEATUREDISABLEONEMOVEMENTKEY_H_GUARD

#undef CFEATUREDISABLEONEMOVEMENTKEY_H_RECURSE_GUARD
#endif //CFEATUREDISABLEONEMOVEMENTKEY_H_RECURSE_GUARD