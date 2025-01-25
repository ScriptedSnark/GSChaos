/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureDelete5RandomEntities.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREDELETE5RANDOMENTITIES_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureDelete5RandomEntities.h
#else //CFEATUREDELETE5RANDOMENTITIES_H_RECURSE_GUARD

#define CFEATUREDELETE5RANDOMENTITIES_H_RECURSE_GUARD

#ifndef CFEATUREDELETE5RANDOMENTITIES_H_GUARD
#define CFEATUREDELETE5RANDOMENTITIES_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureDelete5RandomEntities : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureDelete5RandomEntities.h
#endif //__cplusplus

#endif //CFEATUREDELETE5RANDOMENTITIES_H_GUARD

#undef CFEATUREDELETE5RANDOMENTITIES_H_RECURSE_GUARD
#endif //CFEATUREDELETE5RANDOMENTITIES_H_RECURSE_GUARD