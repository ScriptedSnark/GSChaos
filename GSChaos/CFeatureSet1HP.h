/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureSet1HP.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESET1HP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSet1HP.h
#else //CFEATURESET1HP_H_RECURSE_GUARD

#define CFEATURESET1HP_H_RECURSE_GUARD

#ifndef CFEATURESET1HP_H_GUARD
#define CFEATURESET1HP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSet1HP : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

extern edict_t** sv_player;
//extern edict_t* sv_player;

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSet1HP.h
#endif //__cplusplus

#endif //CFEATURESET1HP_H_GUARD

#undef CFEATURESET1HP_H_RECURSE_GUARD
#endif //CFEATURESET1HP_H_RECURSE_GUARD