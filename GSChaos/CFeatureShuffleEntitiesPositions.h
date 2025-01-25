/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureShuffleEntitiesPositions.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESHUFFLEENTITIESPOSITIONS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureShuffleEntitiesPositions.h
#else //CFEATURESHUFFLEENTITIESPOSITIONS_H_RECURSE_GUARD

#define CFEATURESHUFFLEENTITIESPOSITIONS_H_RECURSE_GUARD

#ifndef CFEATURESHUFFLEENTITIESPOSITIONS_H_GUARD
#define CFEATURESHUFFLEENTITIESPOSITIONS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureShuffleEntitiesPositions : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureShuffleEntitiesPositions.h
#endif //__cplusplus

#endif //CFEATURESHUFFLEENTITIESPOSITIONS_H_GUARD

#undef CFEATURESHUFFLEENTITIESPOSITIONS_H_RECURSE_GUARD
#endif //CFEATURESHUFFLEENTITIESPOSITIONS_H_RECURSE_GUARD