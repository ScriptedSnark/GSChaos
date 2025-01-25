/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureKickWorld.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREKICKWORLD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureKickWorld.h
#else //CFEATUREKICKWORLD_H_RECURSE_GUARD

#define CFEATUREKICKWORLD_H_RECURSE_GUARD

#ifndef CFEATUREKICKWORLD_H_GUARD
#define CFEATUREKICKWORLD_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureKickWorld : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void R_DrawWorld() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	double m_flKickStartTime;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureKickWorld.h
#endif //__cplusplus

#endif //CFEATUREKICKWORLD_H_GUARD

#undef CFEATUREKICKWORLD_H_RECURSE_GUARD
#endif //CFEATUREKICKWORLD_H_RECURSE_GUARD