/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureUltraWideNPCs.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREULTRAWIDENPCS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureUltraWideNPCs.h
#else //CFEATUREULTRAWIDENPCS_H_RECURSE_GUARD

#define CFEATUREULTRAWIDENPCS_H_RECURSE_GUARD

#ifndef CFEATUREULTRAWIDENPCS_H_GUARD
#define CFEATUREULTRAWIDENPCS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureUltraWideNPCs : public CFeatureWideNPCs
{
	void ActivateFeature() override;
	const char* GetFeatureName() override;
	float GetScale() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureUltraWideNPCs.h
#endif //__cplusplus

#endif //CFEATUREULTRAWIDENPCS_H_GUARD

#undef CFEATUREULTRAWIDENPCS_H_RECURSE_GUARD
#endif //CFEATUREULTRAWIDENPCS_H_RECURSE_GUARD