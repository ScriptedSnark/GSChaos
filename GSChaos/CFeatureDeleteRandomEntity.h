/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureDeleteRandomEntity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREDELETERANDOMENTITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureDeleteRandomEntity.h
#else //CFEATUREDELETERANDOMENTITY_H_RECURSE_GUARD

#define CFEATUREDELETERANDOMENTITY_H_RECURSE_GUARD

#ifndef CFEATUREDELETERANDOMENTITY_H_GUARD
#define CFEATUREDELETERANDOMENTITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureDeleteRandomEntity : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureDeleteRandomEntity.h
#endif //__cplusplus

#endif //CFEATUREDELETERANDOMENTITY_H_GUARD

#undef CFEATUREDELETERANDOMENTITY_H_RECURSE_GUARD
#endif //CFEATUREDELETERANDOMENTITY_H_RECURSE_GUARD