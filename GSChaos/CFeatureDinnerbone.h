/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureDinnerbone.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREDINNERBONE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureDinnerbone.h
#else //CFEATUREDINNERBONE_H_RECURSE_GUARD

#define CFEATUREDINNERBONE_H_RECURSE_GUARD

#ifndef CFEATUREDINNERBONE_H_GUARD
#define CFEATUREDINNERBONE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureDinnerbone : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureDinnerbone.h
#endif //__cplusplus

#endif //CFEATUREDINNERBONE_H_GUARD

#undef CFEATUREDINNERBONE_H_RECURSE_GUARD
#endif //CFEATUREDINNERBONE_H_RECURSE_GUARD