/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGruntAmbush.h - description
 *
 * Project (Project desc) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGRUNTAMBUSH_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGruntAmbush.h
#else //CFEATUREGRUNTAMBUSH_H_RECURSE_GUARD

#define CFEATUREGRUNTAMBUSH_H_RECURSE_GUARD

#ifndef CFEATUREGRUNTAMBUSH_H_GUARD
#define CFEATUREGRUNTAMBUSH_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGruntAmbush : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGruntAmbush.h
#endif //__cplusplus

#endif //CFEATUREGRUNTAMBUSH_H_GUARD

#undef CFEATUREGRUNTAMBUSH_H_RECURSE_GUARD
#endif //CFEATUREGRUNTAMBUSH_H_RECURSE_GUARD