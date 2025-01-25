/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureGiveArmor.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGIVEARMOR_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGiveArmor.h
#else //CFEATUREGIVEARMOR_H_RECURSE_GUARD

#define CFEATUREGIVEARMOR_H_RECURSE_GUARD

#ifndef CFEATUREGIVEARMOR_H_GUARD
#define CFEATUREGIVEARMOR_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGiveArmor : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	bool IsGood() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGiveArmor.h
#endif //__cplusplus

#endif //CFEATUREGIVEARMOR_H_GUARD

#undef CFEATUREGIVEARMOR_H_RECURSE_GUARD
#endif //CFEATUREGIVEARMOR_H_RECURSE_GUARD