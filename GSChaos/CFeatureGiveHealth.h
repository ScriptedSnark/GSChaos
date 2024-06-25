/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGiveHealth.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGIVEHEALTH_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGiveHealth.h
#else //CFEATUREGIVEHEALTH_H_RECURSE_GUARD

#define CFEATUREGIVEHEALTH_H_RECURSE_GUARD

#ifndef CFEATUREGIVEHEALTH_H_GUARD
#define CFEATUREGIVEHEALTH_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGiveHealth : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	bool IsGood() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGiveHealth.h
#endif //__cplusplus

#endif //CFEATUREGIVEHEALTH_H_GUARD

#undef CFEATUREGIVEHEALTH_H_RECURSE_GUARD
#endif //CFEATUREGIVEHEALTH_H_RECURSE_GUARD