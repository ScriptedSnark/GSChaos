/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureInvisibleEntities.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREINVISIBLEENTITIES_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureInvisibleEntities.h
#else //CFEATUREINVISIBLEENTITIES_H_RECURSE_GUARD

#define CFEATUREINVISIBLEENTITIES_H_RECURSE_GUARD

#ifndef CFEATUREINVISIBLEENTITIES_H_GUARD
#define CFEATUREINVISIBLEENTITIES_H_GUARD
#pragma once

#ifdef __cplusplus

typedef edict_t* (*_EDICT_NUM)(int n);
extern _EDICT_NUM ORIG_EDICT_NUM;

class CFeatureInvisibleEntities : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;

private:
	bool m_bActivated = false;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureInvisibleEntities.h
#endif //__cplusplus

#endif //CFEATUREINVISIBLEENTITIES_H_GUARD

#undef CFEATUREINVISIBLEENTITIES_H_RECURSE_GUARD
#endif //CFEATUREINVISIBLEENTITIES_H_RECURSE_GUARD