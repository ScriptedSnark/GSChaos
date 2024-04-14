/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureReloadAutosave.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURERELOADAUTOSAVE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureReloadAutosave.h
#else //CFEATURERELOADAUTOSAVE_H_RECURSE_GUARD

#define CFEATURERELOADAUTOSAVE_H_RECURSE_GUARD

#ifndef CFEATURERELOADAUTOSAVE_H_GUARD
#define CFEATURERELOADAUTOSAVE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureReloadAutosave : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureReloadAutosave.h
#endif //__cplusplus

#endif //CFEATURERELOADAUTOSAVE_H_GUARD

#undef CFEATURERELOADAUTOSAVE_H_RECURSE_GUARD
#endif //CFEATURERELOADAUTOSAVE_H_RECURSE_GUARD