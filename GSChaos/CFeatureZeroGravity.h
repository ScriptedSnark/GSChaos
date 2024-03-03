/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureZeroGravity.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREZEROGRAVITY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureZeroGravity.h
#else //CFEATUREZEROGRAVITY_H_RECURSE_GUARD

#define CFEATUREZEROGRAVITY_H_RECURSE_GUARD

#ifndef CFEATUREZEROGRAVITY_H_GUARD
#define CFEATUREZEROGRAVITY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureZeroGravity : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
private:
	bool m_bActivated;
	cvar_t* sv_gravity;
	float m_flOldGravityValue;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureZeroGravity.h
#endif //__cplusplus

#endif //CFEATUREZEROGRAVITY_H_GUARD

#undef CFEATUREZEROGRAVITY_H_RECURSE_GUARD
#endif //CFEATUREZEROGRAVITY_H_RECURSE_GUARD