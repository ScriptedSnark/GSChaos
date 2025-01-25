/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureTinyNPCs.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETINYNPCS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTinyNPCs.h
#else //CFEATURETINYNPCS_H_RECURSE_GUARD

#define CFEATURETINYNPCS_H_RECURSE_GUARD

#ifndef CFEATURETINYNPCS_H_GUARD
#define CFEATURETINYNPCS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureTinyNPCs : public CFeatureWideNPCs
{
	void ActivateFeature() override;
	const char* GetFeatureName() override;
	void Transform(float transform[3][4]) override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureTinyNPCs.h
#endif //__cplusplus

#endif //CFEATURETINYNPCS_H_GUARD

#undef CFEATURETINYNPCS_H_RECURSE_GUARD
#endif //CFEATURETINYNPCS_H_RECURSE_GUARD