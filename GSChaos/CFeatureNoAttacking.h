/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureNoAttacking.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENOATTACKING_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNoAttacking.h
#else //CFEATURENOATTACKING_H_RECURSE_GUARD

#define CFEATURENOATTACKING_H_RECURSE_GUARD

#ifndef CFEATURENOATTACKING_H_GUARD
#define CFEATURENOATTACKING_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNoAttacking : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNoAttacking.h
#endif //__cplusplus

#endif //CFEATURENOATTACKING_H_GUARD

#undef CFEATURENOATTACKING_H_RECURSE_GUARD
#endif //CFEATURENOATTACKING_H_RECURSE_GUARD