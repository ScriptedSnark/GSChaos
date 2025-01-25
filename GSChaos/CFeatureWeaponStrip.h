/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureWeaponStrip.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREWEAPONSTRIP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureWeaponStrip.h
#else //CFEATUREWEAPONSTRIP_H_RECURSE_GUARD

#define CFEATUREWEAPONSTRIP_H_RECURSE_GUARD

#ifndef CFEATUREWEAPONSTRIP_H_GUARD
#define CFEATUREWEAPONSTRIP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureWeaponStrip : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureWeaponStrip.h
#endif //__cplusplus

#endif //CFEATUREWEAPONSTRIP_H_GUARD

#undef CFEATUREWEAPONSTRIP_H_RECURSE_GUARD
#endif //CFEATUREWEAPONSTRIP_H_RECURSE_GUARD