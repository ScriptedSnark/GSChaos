/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureMLGAudio.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMLGAUDIO_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMLGAudio.h
#else //CFEATUREMLGAUDIO_H_RECURSE_GUARD

#define CFEATUREMLGAUDIO_H_RECURSE_GUARD

#ifndef CFEATUREMLGAUDIO_H_GUARD
#define CFEATUREMLGAUDIO_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bMLGAudio;
extern std::vector<std::string> g_szMLGSounds;

class CFeatureMLGAudio : public CChaosFeature
{
	void ParseMLGDirectory();
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureMLGAudio.h
#endif //__cplusplus

#endif //CFEATUREMLGAUDIO_H_GUARD

#undef CFEATUREMLGAUDIO_H_RECURSE_GUARD
#endif //CFEATUREMLGAUDIO_H_RECURSE_GUARD