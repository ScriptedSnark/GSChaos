/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureChipmunks.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURECHIPMUNKS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureChipmunks.h
#else //CFEATURECHIPMUNKS_H_RECURSE_GUARD

#define CFEATURECHIPMUNKS_H_RECURSE_GUARD

#ifndef CFEATURECHIPMUNKS_H_GUARD
#define CFEATURECHIPMUNKS_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedChipmunks;

class CFeatureChipmunks : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureChipmunks.h
#endif //__cplusplus

#endif //CFEATURECHIPMUNKS_H_GUARD

#undef CFEATURECHIPMUNKS_H_RECURSE_GUARD
#endif //CFEATURECHIPMUNKS_H_RECURSE_GUARD