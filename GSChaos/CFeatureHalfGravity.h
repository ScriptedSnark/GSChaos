/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureHalfGravity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREHALFGRAVITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureHalfGravity.h
#else //CFEATUREHALFGRAVITY_H_RECURSE_GUARD

#define CFEATUREHALFGRAVITY_H_RECURSE_GUARD

#ifndef CFEATUREHALFGRAVITY_H_GUARD
#define CFEATUREHALFGRAVITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureHalfGravity : public CFeatureHighGravity
{
	const char* GetFeatureName() override;
	float GetGravityValue() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureHalfGravity.h
#endif //__cplusplus

#endif //CFEATUREHALFGRAVITY_H_GUARD

#undef CFEATUREHALFGRAVITY_H_RECURSE_GUARD
#endif //CFEATUREHALFGRAVITY_H_RECURSE_GUARD