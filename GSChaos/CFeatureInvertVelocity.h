/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureInvertVelocity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREINVERTVELOCITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureInvertVelocity.h
#else //CFEATUREINVERTVELOCITY_H_RECURSE_GUARD

#define CFEATUREINVERTVELOCITY_H_RECURSE_GUARD

#ifndef CFEATUREINVERTVELOCITY_H_GUARD
#define CFEATUREINVERTVELOCITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureInvertVelocity : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureInvertVelocity.h
#endif //__cplusplus

#endif //CFEATUREINVERTVELOCITY_H_GUARD

#undef CFEATUREINVERTVELOCITY_H_RECURSE_GUARD
#endif //CFEATUREINVERTVELOCITY_H_RECURSE_GUARD