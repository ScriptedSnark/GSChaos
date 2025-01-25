/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureSpawn5RandomEntities.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESPAWN5RANDOMENTITIES_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSpawn5RandomEntities.h
#else //CFEATURESPAWN5RANDOMENTITIES_H_RECURSE_GUARD

#define CFEATURESPAWN5RANDOMENTITIES_H_RECURSE_GUARD

#ifndef CFEATURESPAWN5RANDOMENTITIES_H_GUARD
#define CFEATURESPAWN5RANDOMENTITIES_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSpawn5RandomEntities : public CFeatureSpawnRandomEntity
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSpawn5RandomEntities.h
#endif //__cplusplus

#endif //CFEATURESPAWN5RANDOMENTITIES_H_GUARD

#undef CFEATURESPAWN5RANDOMENTITIES_H_RECURSE_GUARD
#endif //CFEATURESPAWN5RANDOMENTITIES_H_RECURSE_GUARD