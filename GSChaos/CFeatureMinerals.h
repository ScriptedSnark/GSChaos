/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureMinerals.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMINERALS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMinerals.h
#else //CFEATUREMINERALS_H_RECURSE_GUARD

#define CFEATUREMINERALS_H_RECURSE_GUARD

#ifndef CFEATUREMINERALS_H_GUARD
#define CFEATUREMINERALS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureMinerals : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname) override;
	void Restore() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	int m_iCrystalModel;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureMinerals.h
#endif //__cplusplus

#endif //CFEATUREMINERALS_H_GUARD

#undef CFEATUREMINERALS_H_RECURSE_GUARD
#endif //CFEATUREMINERALS_H_RECURSE_GUARD