/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureSpawnRandomEntity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESPAWNRANDOMENTITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSpawnRandomEntity.h
#else //CFEATURESPAWNRANDOMENTITY_H_RECURSE_GUARD

#define CFEATURESPAWNRANDOMENTITY_H_RECURSE_GUARD

#ifndef CFEATURESPAWNRANDOMENTITY_H_GUARD
#define CFEATURESPAWNRANDOMENTITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSpawnRandomEntity : public CChaosFeature
{
public:
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
private:
	const char* m_pszEntityName;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSpawnRandomEntity.h
#endif //__cplusplus

#endif //CFEATURESPAWNRANDOMENTITY_H_GUARD

#undef CFEATURESPAWNRANDOMENTITY_H_RECURSE_GUARD
#endif //CFEATURESPAWNRANDOMENTITY_H_RECURSE_GUARD