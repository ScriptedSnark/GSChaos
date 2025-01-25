/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureWideScreen.h
 *
 * Project (GSChaos) header file
 * Authors: StereoBucket.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREBLUR_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureBlur.h
#else //CFEATUREBLUR_H_RECURSE_GUARD

#define CFEATUREBLUR_H_RECURSE_GUARD

#ifndef CFEATUREBLUR_H_GUARD
#define CFEATUREBLUR_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedBlur;

class CFeatureBlur : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void SwapBuffers() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
private:
	cvar_t* fps_max;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureBlur.h
#endif //__cplusplus

#endif //CFEATUREBLUR_H_GUARD

#undef CFEATUREBLUR_H_RECURSE_GUARD
#endif //CFEATUREBLUR_H_RECURSE_GUARD