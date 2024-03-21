/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureStop.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESTOP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureStop.h
#else //CFEATURESTOP_H_RECURSE_GUARD

#define CFEATURESTOP_H_RECURSE_GUARD

#ifndef CFEATURESTOP_H_GUARD
#define CFEATURESTOP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureStop : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureStop.h
#endif //__cplusplus

#endif //CFEATURESTOP_H_GUARD

#undef CFEATURESTOP_H_RECURSE_GUARD
#endif //CFEATURESTOP_H_RECURSE_GUARD