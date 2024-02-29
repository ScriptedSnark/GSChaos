/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureHighGravity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREHIGHGRAVITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureHighGravity.h
#else //CFEATUREHIGHGRAVITY_H_RECURSE_GUARD

#define CFEATUREHIGHGRAVITY_H_RECURSE_GUARD

#ifndef CFEATUREHIGHGRAVITY_H_GUARD
#define CFEATUREHIGHGRAVITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureHighGravity : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureHighGravity.h
#endif //__cplusplus

#endif //CFEATUREHIGHGRAVITY_H_GUARD

#undef CFEATUREHIGHGRAVITY_H_RECURSE_GUARD
#endif //CFEATUREHIGHGRAVITY_H_RECURSE_GUARD