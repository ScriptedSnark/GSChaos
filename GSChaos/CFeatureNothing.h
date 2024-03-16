/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureNothing.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENOTHING_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNothing.h
#else //CFEATURENOTHING_H_RECURSE_GUARD

#define CFEATURENOTHING_H_RECURSE_GUARD

#ifndef CFEATURENOTHING_H_GUARD
#define CFEATURENOTHING_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNothing : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNothing.h
#endif //__cplusplus

#endif //CFEATURENOTHING_H_GUARD

#undef CFEATURENOTHING_H_RECURSE_GUARD
#endif //CFEATURENOTHING_H_RECURSE_GUARD