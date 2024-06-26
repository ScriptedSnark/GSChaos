/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureModelInsanity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMODELINSANITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureModelInsanity.h
#else //CFEATUREMODELINSANITY_H_RECURSE_GUARD

#define CFEATUREMODELINSANITY_H_RECURSE_GUARD

#ifndef CFEATUREMODELINSANITY_H_GUARD
#define CFEATUREMODELINSANITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureModelInsanity : public CFeatureWideNPCs
{
	void ActivateFeature() override;
	const char* GetFeatureName() override;
	void Transform(float transform[3][4]) override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureModelInsanity.h
#endif //__cplusplus

#endif //CFEATUREMODELINSANITY_H_GUARD

#undef CFEATUREMODELINSANITY_H_RECURSE_GUARD
#endif //CFEATUREMODELINSANITY_H_RECURSE_GUARD