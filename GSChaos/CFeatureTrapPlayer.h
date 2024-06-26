/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureTrapPlayer.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETRAPPLAYER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTrapPlayer.h
#else //CFEATURETRAPPLAYER_H_RECURSE_GUARD

#define CFEATURETRAPPLAYER_H_RECURSE_GUARD

#ifndef CFEATURETRAPPLAYER_H_GUARD
#define CFEATURETRAPPLAYER_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureTrapPlayer : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	void Restore() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	double m_flSaveTime;
	bool m_bTrap;
	edict_t* m_pTrap;
	Vector m_vOrigin;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureTrapPlayer.h
#endif //__cplusplus

#endif //CFEATURETRAPPLAYER_H_GUARD

#undef CFEATURETRAPPLAYER_H_RECURSE_GUARD
#endif //CFEATURETRAPPLAYER_H_RECURSE_GUARD