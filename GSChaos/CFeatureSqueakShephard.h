/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureSqueakShephard.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESQUEAKSHEPHARD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSqueakShephard.h
#else //CFEATURESQUEAKSHEPHARD_H_RECURSE_GUARD

#define CFEATURESQUEAKSHEPHARD_H_RECURSE_GUARD

#ifndef CFEATURESQUEAKSHEPHARD_H_GUARD
#define CFEATURESQUEAKSHEPHARD_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSqueakShephard : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
public:
	virtual edict_t* SpawnSqueak();
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSqueakShephard.h
#endif //__cplusplus

#endif //CFEATURESQUEAKSHEPHARD_H_GUARD

#undef CFEATURESQUEAKSHEPHARD_H_RECURSE_GUARD
#endif //CFEATURESQUEAKSHEPHARD_H_RECURSE_GUARD