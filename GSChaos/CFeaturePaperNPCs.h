/**
 * Copyright - ScriptedSnark, 2024.
 * CFeaturePaperNPCs.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREPAPERNPCS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeaturePaperNPCs.h
#else //CFEATUREPAPERNPCS_H_RECURSE_GUARD

#define CFEATUREPAPERNPCS_H_RECURSE_GUARD

#ifndef CFEATUREPAPERNPCS_H_GUARD
#define CFEATUREPAPERNPCS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeaturePaperNPCs : public CFeatureWideNPCs
{
	void ActivateFeature() override;
	const char* GetFeatureName() override;
	void Transform(float transform[3][4]) override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeaturePaperNPCs.h
#endif //__cplusplus

#endif //CFEATUREPAPERNPCS_H_GUARD

#undef CFEATUREPAPERNPCS_H_RECURSE_GUARD
#endif //CFEATUREPAPERNPCS_H_RECURSE_GUARD