/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureReplaceModelsWithPlayer.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREREPLACEMODELSWITHPLAYER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureReplaceModelsWithPlayer.h
#else //CFEATUREREPLACEMODELSWITHPLAYER_H_RECURSE_GUARD

#define CFEATUREREPLACEMODELSWITHPLAYER_H_RECURSE_GUARD

#ifndef CFEATUREREPLACEMODELSWITHPLAYER_H_GUARD
#define CFEATUREREPLACEMODELSWITHPLAYER_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureReplaceModelsWithPlayer : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname) override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;

#ifdef COF_BUILD
private:
	int m_iSimonModel;
#endif
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureReplaceModelsWithPlayer.h
#endif //__cplusplus

#endif //CFEATUREREPLACEMODELSWITHPLAYER_H_GUARD

#undef CFEATUREREPLACEMODELSWITHPLAYER_H_RECURSE_GUARD
#endif //CFEATUREREPLACEMODELSWITHPLAYER_H_RECURSE_GUARD