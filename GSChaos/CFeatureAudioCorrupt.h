/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureAudioCorrupt.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREAUDIOCORRUPT_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureAudioCorrupt.h
#else //CFEATUREAUDIOCORRUPT_H_RECURSE_GUARD

#define CFEATUREAUDIOCORRUPT_H_RECURSE_GUARD

#ifndef CFEATUREAUDIOCORRUPT_H_GUARD
#define CFEATUREAUDIOCORRUPT_H_GUARD
#pragma once

#ifdef __cplusplus

extern volatile dma_t* shm;

class CFeatureAudioCorrupt : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override { return true; }

private:
	bool m_bActivated;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureAudioCorrupt.h
#endif //__cplusplus

#endif //CFEATUREAUDIOCORRUPT_H_GUARD

#undef CFEATUREAUDIOCORRUPT_H_RECURSE_GUARD
#endif //CFEATUREAUDIOCORRUPT_H_RECURSE_GUARD