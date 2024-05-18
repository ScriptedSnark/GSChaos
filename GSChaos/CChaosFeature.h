/**
 * Copyright - ScriptedSnark, 2024.
 * CChaosFeature.h - chaos feature
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CCHAOSFEATURE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CChaosFeature.h
#else //CCHAOSFEATURE_H_RECURSE_GUARD

#define CCHAOSFEATURE_H_RECURSE_GUARD

#ifndef CCHAOSFEATURE_H_GUARD
#define CCHAOSFEATURE_H_GUARD
#pragma once

#ifdef __cplusplus

class CChaosFeature
{
public:
	virtual void Init();
	virtual void ActivateFeature();
	virtual void DeactivateFeature();
	virtual void OnFrame(double time);
	virtual void ExpireThink();
	virtual const char* GetFeatureName();
	virtual void Draw();
	virtual void ResetStates();
	virtual void Restore();
	virtual void HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname);
	virtual void SwapBuffers();
	virtual void PM_Jump();
	virtual bool IsActive();
	virtual double GetDuration();
	virtual bool UseCustomDuration();

	double m_flExpireTime;
private:
	bool m_bActivated;
};

extern std::vector<CChaosFeature*> gChaosFeatures;
extern std::vector<const char*> gChaosFeaturesNames;

template <typename T>
inline T* RegisterChaosFeature()
{
	T* p = new T();
	gChaosFeatures.push_back(p);
	return p;
}

#else //!__cplusplus
#error C++ compiler required to compile CChaosFeature.h
#endif //__cplusplus

#endif //CCHAOSFEATURE_H_GUARD

#undef CCHAOSFEATURE_H_RECURSE_GUARD
#endif //CCHAOSFEATURE_H_RECURSE_GUARD