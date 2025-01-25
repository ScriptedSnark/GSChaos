/**
 * Copyright - ScriptedSnark, 2024-2025.
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
	virtual void HUD_CreateEntities();
	virtual void HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname);
	virtual void SwapBuffers();
	virtual void R_DrawWorld();
	virtual void PM_Jump();
	virtual void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active);
	virtual void PM_Move(struct playermove_s* ppmove, qboolean server);
	virtual void Vote(const std::string& user, const std::string& msg);
	virtual void V_CalcRefdef(struct ref_params_s* pparams);
	virtual void VidInit();
	virtual bool IsActive();
	virtual double GetDuration();
	virtual bool UseCustomDuration();
	virtual bool IsGood();
	virtual bool CanBeInfinite();
	virtual void SetVoterNickname(const std::string& name);
	virtual const char* GetVoterNickname();

	double m_flExpireTime;
private:
	bool m_bActivated;
	std::string m_szPreservedVoterName;
	std::string m_szVoterName;
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