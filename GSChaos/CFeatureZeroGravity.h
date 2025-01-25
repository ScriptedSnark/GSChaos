/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureZeroGravity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREZEROGRAVITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureZeroGravity.h
#else //CFEATUREZEROGRAVITY_H_RECURSE_GUARD

#define CFEATUREZEROGRAVITY_H_RECURSE_GUARD

#ifndef CFEATUREZEROGRAVITY_H_GUARD
#define CFEATUREZEROGRAVITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureZeroGravity : public CFeatureHighGravity
{
	const char* GetFeatureName() override;
	float GetGravityValue() override;
	double GetDuration() override;
	bool UseCustomDuration() override;	
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureZeroGravity.h
#endif //__cplusplus

#endif //CFEATUREZEROGRAVITY_H_GUARD

#undef CFEATUREZEROGRAVITY_H_RECURSE_GUARD
#endif //CFEATUREZEROGRAVITY_H_RECURSE_GUARD