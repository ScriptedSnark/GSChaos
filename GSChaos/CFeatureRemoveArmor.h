/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureRemoveArmor.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREREMOVEARMOR_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureRemoveArmor.h
#else //CFEATUREREMOVEARMOR_H_RECURSE_GUARD

#define CFEATUREREMOVEARMOR_H_RECURSE_GUARD

#ifndef CFEATUREREMOVEARMOR_H_GUARD
#define CFEATUREREMOVEARMOR_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureRemoveArmor : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureRemoveArmor.h
#endif //__cplusplus

#endif //CFEATUREREMOVEARMOR_H_GUARD

#undef CFEATUREREMOVEARMOR_H_RECURSE_GUARD
#endif //CFEATUREREMOVEARMOR_H_RECURSE_GUARD