/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGiveOneArmor.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGIVEONEARMOR_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGiveOneArmor.h
#else //CFEATUREGIVEONEARMOR_H_RECURSE_GUARD

#define CFEATUREGIVEONEARMOR_H_RECURSE_GUARD

#ifndef CFEATUREGIVEONEARMOR_H_GUARD
#define CFEATUREGIVEONEARMOR_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGiveOneArmor : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	bool IsGood() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGiveOneArmor.h
#endif //__cplusplus

#endif //CFEATUREGIVEONEARMOR_H_GUARD

#undef CFEATUREGIVEONEARMOR_H_RECURSE_GUARD
#endif //CFEATUREGIVEONEARMOR_H_RECURSE_GUARD