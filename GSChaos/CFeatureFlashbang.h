/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureFlashbang.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREFLASHBANG_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureFlashbang.h
#else //CFEATUREFLASHBANG_H_RECURSE_GUARD

#define CFEATUREFLASHBANG_H_RECURSE_GUARD

#ifndef CFEATUREFLASHBANG_H_GUARD
#define CFEATUREFLASHBANG_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureFlashbang : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureFlashbang.h
#endif //__cplusplus

#endif //CFEATUREFLASHBANG_H_GUARD

#undef CFEATUREFLASHBANG_H_RECURSE_GUARD
#endif //CFEATUREFLASHBANG_H_RECURSE_GUARD