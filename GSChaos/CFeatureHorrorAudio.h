/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureHorrorAudio.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREHORRORAUDIO_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureHorrorAudio.h
#else //CFEATUREHORRORAUDIO_H_RECURSE_GUARD

#define CFEATUREHORRORAUDIO_H_RECURSE_GUARD

#ifndef CFEATUREHORRORAUDIO_H_GUARD
#define CFEATUREHORRORAUDIO_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedHorrorAudio;

class CFeatureHorrorAudio : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override { return true; }
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureHorrorAudio.h
#endif //__cplusplus

#endif //CFEATUREHORRORAUDIO_H_GUARD

#undef CFEATUREHORRORAUDIO_H_RECURSE_GUARD
#endif //CFEATUREHORRORAUDIO_H_RECURSE_GUARD