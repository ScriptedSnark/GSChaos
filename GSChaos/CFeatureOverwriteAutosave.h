/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureOverwriteAutosave.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREOVERWRITEAUTOSAVE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureOverwriteAutosave.h
#else //CFEATUREOVERWRITEAUTOSAVE_H_RECURSE_GUARD

#define CFEATUREOVERWRITEAUTOSAVE_H_RECURSE_GUARD

#ifndef CFEATUREOVERWRITEAUTOSAVE_H_GUARD
#define CFEATUREOVERWRITEAUTOSAVE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureOverwriteAutosave : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureOverwriteAutosave.h
#endif //__cplusplus

#endif //CFEATUREOVERWRITEAUTOSAVE_H_GUARD

#undef CFEATUREOVERWRITEAUTOSAVE_H_RECURSE_GUARD
#endif //CFEATUREOVERWRITEAUTOSAVE_H_RECURSE_GUARD