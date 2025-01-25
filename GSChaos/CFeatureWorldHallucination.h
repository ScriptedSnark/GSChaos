/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureWorldHallucination.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREWORLDHALLUCINATION_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureWorldHallucination.h
#else //CFEATUREWORLDHALLUCINATION_H_RECURSE_GUARD

#define CFEATUREWORLDHALLUCINATION_H_RECURSE_GUARD

#ifndef CFEATUREWORLDHALLUCINATION_H_GUARD
#define CFEATUREWORLDHALLUCINATION_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureWorldHallucination : public CFeatureMonsterWorldspawn
{
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureWorldHallucination.h
#endif //__cplusplus

#endif //CFEATUREWORLDHALLUCINATION_H_GUARD

#undef CFEATUREWORLDHALLUCINATION_H_RECURSE_GUARD
#endif //CFEATUREWORLDHALLUCINATION_H_RECURSE_GUARD