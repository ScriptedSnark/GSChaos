/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGiveAllWeapons.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGIVEALLWEAPONS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGiveAllWeapons.h
#else //CFEATUREGIVEALLWEAPONS_H_RECURSE_GUARD

#define CFEATUREGIVEALLWEAPONS_H_RECURSE_GUARD

#ifndef CFEATUREGIVEALLWEAPONS_H_GUARD
#define CFEATUREGIVEALLWEAPONS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGiveAllWeapons : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	bool IsGood() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGiveAllWeapons.h
#endif //__cplusplus

#endif //CFEATUREGIVEALLWEAPONS_H_GUARD

#undef CFEATUREGIVEALLWEAPONS_H_RECURSE_GUARD
#endif //CFEATUREGIVEALLWEAPONS_H_RECURSE_GUARD