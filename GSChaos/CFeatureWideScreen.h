/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureWideScreen.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREWIDESCREEN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureWideScreen.h
#else //CFEATUREWIDESCREEN_H_RECURSE_GUARD

#define CFEATUREWIDESCREEN_H_RECURSE_GUARD

#ifndef CFEATUREWIDESCREEN_H_GUARD
#define CFEATUREWIDESCREEN_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedWideScreen;

class CFeatureWideScreen : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void SwapBuffers() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureWideScreen.h
#endif //__cplusplus

#endif //CFEATUREWIDESCREEN_H_GUARD

#undef CFEATUREWIDESCREEN_H_RECURSE_GUARD
#endif //CFEATUREWIDESCREEN_H_RECURSE_GUARD