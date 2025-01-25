/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureMonsterWorldspawn.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMONSTERWORLDSPAWN_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMonsterWorldspawn.h
#else //CFEATUREMONSTERWORLDSPAWN_H_RECURSE_GUARD

#define CFEATUREMONSTERWORLDSPAWN_H_RECURSE_GUARD

#ifndef CFEATUREMONSTERWORLDSPAWN_H_GUARD
#define CFEATUREMONSTERWORLDSPAWN_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureMonsterWorldspawn : public CChaosFeature
{
public:
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	virtual edict_t* GetWorldspawnEdict();
private:
	edict_t* monster_worldspawn;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureMonsterWorldspawn.h
#endif //__cplusplus

#endif //CFEATUREMONSTERWORLDSPAWN_H_GUARD

#undef CFEATUREMONSTERWORLDSPAWN_H_RECURSE_GUARD
#endif //CFEATUREMONSTERWORLDSPAWN_H_RECURSE_GUARD