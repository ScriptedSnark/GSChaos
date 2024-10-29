/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureCreepypasta.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURECREEPYPASTA_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureCreepypasta.h
#else //CFEATURECREEPYPASTA_H_RECURSE_GUARD

#define CFEATURECREEPYPASTA_H_RECURSE_GUARD

#ifndef CFEATURECREEPYPASTA_H_GUARD
#define CFEATURECREEPYPASTA_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureCreepypasta : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void SwapBuffers() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureCreepypasta.h
#endif //__cplusplus

#endif //CFEATURECREEPYPASTA_H_GUARD

#undef CFEATURECREEPYPASTA_H_RECURSE_GUARD
#endif //CFEATURECREEPYPASTA_H_RECURSE_GUARD