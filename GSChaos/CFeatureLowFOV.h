/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureLowFOV.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURELOWFOV_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureLowFOV.h
#else //CFEATURELOWFOV_H_RECURSE_GUARD

#define CFEATURELOWFOV_H_RECURSE_GUARD

#ifndef CFEATURELOWFOV_H_GUARD
#define CFEATURELOWFOV_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureLowFOV : public CFeatureQuakePro
{
	void Init() override;
	const char* GetFeatureName() override;
	float GetFOV() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureLowFOV.h
#endif //__cplusplus

#endif //CFEATURELOWFOV_H_GUARD

#undef CFEATURELOWFOV_H_RECURSE_GUARD
#endif //CFEATURELOWFOV_H_RECURSE_GUARD