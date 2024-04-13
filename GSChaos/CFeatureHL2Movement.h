/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureHL2Movement.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREHL2MOVEMENT_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureHL2Movement.h
#else //CFEATUREHL2MOVEMENT_H_RECURSE_GUARD

#define CFEATUREHL2MOVEMENT_H_RECURSE_GUARD

#ifndef CFEATUREHL2MOVEMENT_H_GUARD
#define CFEATUREHL2MOVEMENT_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedHL2Movement;

class CFeatureHL2Movement : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void PM_Jump() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureHL2Movement.h
#endif //__cplusplus

#endif //CFEATUREHL2MOVEMENT_H_GUARD

#undef CFEATUREHL2MOVEMENT_H_RECURSE_GUARD
#endif //CFEATUREHL2MOVEMENT_H_RECURSE_GUARD