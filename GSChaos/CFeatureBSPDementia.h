/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureRotateWorld.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREROTATEWORLD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureRotateWorld.h
#else //CFEATUREROTATEWORLD_H_RECURSE_GUARD

#define CFEATUREROTATEWORLD_H_RECURSE_GUARD

#ifndef CFEATUREROTATEWORLD_H_GUARD
#define CFEATUREROTATEWORLD_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureBSPDementia : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
private:
	bool m_bActivated;
	msurface_t* m_pSurfaces;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureRotateWorld.h
#endif //__cplusplus

#endif //CFEATUREROTATEWORLD_H_GUARD

#undef CFEATUREROTATEWORLD_H_RECURSE_GUARD
#endif //CFEATUREROTATEWORLD_H_RECURSE_GUARD