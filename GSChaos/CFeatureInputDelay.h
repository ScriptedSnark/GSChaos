/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureInputDelay.h
 *
 * Project (GSChaos) header file
 * Authors: StereoBucket.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREINPUTDELAY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureInputDelay.h
#else //CFEATUREINPUTDELAY_H_RECURSE_GUARD

#define CFEATUREINPUTDELAY_H_RECURSE_GUARD

#ifndef CFEATUREINPUTDELAY_H_GUARD
#define CFEATUREINPUTDELAY_H_GUARD
#pragma once

#ifdef __cplusplus
#include <queue>

class CFeatureInputDelay : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void Restore() override;
	void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active) override;
	void VidInit() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
private:
	bool m_first;
	usercmd_s m_lastcmd;
	struct usercmd_time_s
	{
		usercmd_s cmd;
		double time;
	};
	bool m_vfirst;
	float m_lastview[3];
	struct viewangles_time_s
	{
		float vangles[3];
		double time;
	};
	std::queue<usercmd_time_s> m_commandQueue;
	std::queue<viewangles_time_s> m_viewQueue;
	cvar_t *cl_pitchup, *cl_pitchdown;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureInputDelay.h
#endif //__cplusplus

#endif //CFEATUREINPUTDELAY_H_GUARD

#undef CFEATUREINPUTDELAY_H_GUARD
#endif //CFEATUREINPUTDELAY_H_RECURSE_GUARD