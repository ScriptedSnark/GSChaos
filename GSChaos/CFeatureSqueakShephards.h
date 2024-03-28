/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureSqueakShephards.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESQUEAKSHEPHARDS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSqueakShephards.h
#else //CFEATURESQUEAKSHEPHARDS_H_RECURSE_GUARD

#define CFEATURESQUEAKSHEPHARDS_H_RECURSE_GUARD

#ifndef CFEATURESQUEAKSHEPHARDS_H_GUARD
#define CFEATURESQUEAKSHEPHARDS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSqueakShephards : public CFeatureSqueakShephard
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSqueakShephards.h
#endif //__cplusplus

#endif //CFEATURESQUEAKSHEPHARDS_H_GUARD

#undef CFEATURESQUEAKSHEPHARDS_H_RECURSE_GUARD
#endif //CFEATURESQUEAKSHEPHARDS_H_RECURSE_GUARD