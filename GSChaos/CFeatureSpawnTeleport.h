/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureSpawnTeleport.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESPAWNTELEPORT_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSpawnTeleport.h
#else //CFEATURESPAWNTELEPORT_H_RECURSE_GUARD

#define CFEATURESPAWNTELEPORT_H_RECURSE_GUARD

#ifndef CFEATURESPAWNTELEPORT_H_GUARD
#define CFEATURESPAWNTELEPORT_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSpawnTeleport : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSpawnTeleport.h
#endif //__cplusplus

#endif //CFEATURESPAWNTELEPORT_H_GUARD

#undef CFEATURESPAWNTELEPORT_H_RECURSE_GUARD
#endif //CFEATURESPAWNTELEPORT_H_RECURSE_GUARD