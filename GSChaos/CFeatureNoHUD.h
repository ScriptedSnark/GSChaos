/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureNoHUD.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENOHUD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNoHUD.h
#else //CFEATURENOHUD_H_RECURSE_GUARD

#define CFEATURENOHUD_H_RECURSE_GUARD

#ifndef CFEATURENOHUD_H_GUARD
#define CFEATURENOHUD_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNoHUD : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
#ifdef COF_BUILD
	void OnFrame(double time) override;
#endif
	const char* GetFeatureName() override;
#ifdef COF_BUILD
private:
	cvar_t* hud_draw;
#endif
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNoHUD.h
#endif //__cplusplus

#endif //CFEATURENOHUD_H_GUARD

#undef CFEATURENOHUD_H_RECURSE_GUARD
#endif //CFEATURENOHUD_H_RECURSE_GUARD