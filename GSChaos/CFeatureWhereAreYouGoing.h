/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureWhereAreYouGoing.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREWHEREAREYOUGOING_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureWhereAreYouGoing.h
#else //CFEATUREWHEREAREYOUGOING_H_RECURSE_GUARD

#define CFEATUREWHEREAREYOUGOING_H_RECURSE_GUARD

#ifndef CFEATUREWHEREAREYOUGOING_H_GUARD
#define CFEATUREWHEREAREYOUGOING_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureWhereAreYouGoing : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	void Restore() override;
private:
	Vector m_vSavedOrigin;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureWhereAreYouGoing.h
#endif //__cplusplus

#endif //CFEATUREWHEREAREYOUGOING_H_GUARD

#undef CFEATUREWHEREAREYOUGOING_H_RECURSE_GUARD
#endif //CFEATUREWHEREAREYOUGOING_H_RECURSE_GUARD