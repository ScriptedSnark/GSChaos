/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureTallWorld.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETALLWORLD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTallWorld.h
#else //CFEATURETALLWORLD_H_RECURSE_GUARD

#define CFEATURETALLWORLD_H_RECURSE_GUARD

#ifndef CFEATURETALLWORLD_H_GUARD
#define CFEATURETALLWORLD_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureTallWorld : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void R_DrawWorld() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureTallWorld.h
#endif //__cplusplus

#endif //CFEATURETALLWORLD_H_GUARD

#undef CFEATURETALLWORLD_H_RECURSE_GUARD
#endif //CFEATURETALLWORLD_H_RECURSE_GUARD