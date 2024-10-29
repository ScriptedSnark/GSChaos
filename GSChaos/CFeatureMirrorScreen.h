/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureMirrorScreen.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMIRRORSCREEN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMirrorScreen.h
#else //CFEATUREMIRRORSCREEN_H_RECURSE_GUARD

#define CFEATUREMIRRORSCREEN_H_RECURSE_GUARD

#ifndef CFEATUREMIRRORSCREEN_H_GUARD
#define CFEATUREMIRRORSCREEN_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedMirror;

class CFeatureMirrorScreen : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void SwapBuffers() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureMirrorScreen.h
#endif //__cplusplus

#endif //CFEATUREMIRRORSCREEN_H_GUARD

#undef CFEATUREMIRRORSCREEN_H_RECURSE_GUARD
#endif //CFEATUREMIRRORSCREEN_H_RECURSE_GUARD