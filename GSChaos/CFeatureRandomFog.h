/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureRandomFog.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURERANDOMFOG_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureRandomFog.h
#else //CFEATURERANDOMFOG_H_RECURSE_GUARD

#define CFEATURERANDOMFOG_H_RECURSE_GUARD

#ifndef CFEATURERANDOMFOG_H_GUARD
#define CFEATURERANDOMFOG_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureRandomFog : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureRandomFog.h
#endif //__cplusplus

#endif //CFEATURERANDOMFOG_H_GUARD

#undef CFEATURERANDOMFOG_H_RECURSE_GUARD
#endif //CFEATURERANDOMFOG_H_RECURSE_GUARD