/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureThirdPerson.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETHIRDPERSON_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureThirdPerson.h
#else //CFEATURETHIRDPERSON_H_RECURSE_GUARD

#define CFEATURETHIRDPERSON_H_RECURSE_GUARD

#ifndef CFEATURETHIRDPERSON_H_GUARD
#define CFEATURETHIRDPERSON_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureThirdPerson : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureThirdPerson.h
#endif //__cplusplus

#endif //CFEATURETHIRDPERSON_H_GUARD

#undef CFEATURETHIRDPERSON_H_RECURSE_GUARD
#endif //CFEATURETHIRDPERSON_H_RECURSE_GUARD