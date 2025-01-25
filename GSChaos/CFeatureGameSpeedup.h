/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureGameSpeedup.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGAMESPEEDUP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGameSpeedup.h
#else //CFEATUREGAMESPEEDUP_H_RECURSE_GUARD

#define CFEATUREGAMESPEEDUP_H_RECURSE_GUARD

#ifndef CFEATUREGAMESPEEDUP_H_GUARD
#define CFEATUREGAMESPEEDUP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGameSpeedup : public CFeatureHalfGameSpeed
{
	const char* GetFeatureName() override;
	float GetTimescale() override;
	double GetDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGameSpeedup.h
#endif //__cplusplus

#endif //CFEATUREGAMESPEEDUP_H_GUARD

#undef CFEATUREGAMESPEEDUP_H_RECURSE_GUARD
#endif //CFEATUREGAMESPEEDUP_H_RECURSE_GUARD