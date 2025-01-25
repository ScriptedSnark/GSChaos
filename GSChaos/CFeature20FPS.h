/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeature20FPS.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURE20FPS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeature20FPS.h
#else //CFEATURE20FPS_H_RECURSE_GUARD

#define CFEATURE20FPS_H_RECURSE_GUARD

#ifndef CFEATURE20FPS_H_GUARD
#define CFEATURE20FPS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeature20FPS : public CChaosFeature
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
	bool m_bVSyncEnabled;
	cvar_t* fps_max;
	cvar_t* gl_vsync;
	float fps_value;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeature20FPS.h
#endif //__cplusplus

#endif //CFEATURE20FPS_H_GUARD

#undef CFEATURE20FPS_H_RECURSE_GUARD
#endif //CFEATURE20FPS_H_RECURSE_GUARD