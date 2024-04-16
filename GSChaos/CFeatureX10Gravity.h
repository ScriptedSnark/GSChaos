/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureX10Gravity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREX10GRAVITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureX10Gravity.h
#else //CFEATUREX10GRAVITY_H_RECURSE_GUARD

#define CFEATUREX10GRAVITY_H_RECURSE_GUARD

#ifndef CFEATUREX10GRAVITY_H_GUARD
#define CFEATUREX10GRAVITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureX10Gravity : public CFeatureHighGravity
{
	const char* GetFeatureName() override;
	float GetGravityValue() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureX10Gravity.h
#endif //__cplusplus

#endif //CFEATUREX10GRAVITY_H_GUARD

#undef CFEATUREX10GRAVITY_H_RECURSE_GUARD
#endif //CFEATUREX10GRAVITY_H_RECURSE_GUARD