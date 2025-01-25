/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureLobotomy.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURELOBOTOMY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureLobotomy.h
#else //CFEATURELOBOTOMY_H_RECURSE_GUARD

#define CFEATURELOBOTOMY_H_RECURSE_GUARD

#ifndef CFEATURELOBOTOMY_H_GUARD
#define CFEATURELOBOTOMY_H_GUARD
#pragma once

#ifdef __cplusplus

#define LOBOTOMY_TP_TIME 8.0

class CFeatureLobotomy : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	void DoMegaLobotomy(double time);
private:
	bool m_bActivated;
	bool m_bPlayedSound;
	bool m_bInitializedSecondPos;
	double m_flLobotomyTPTime;
	Vector m_lobotomyOrigin[2];
	Vector m_lobotomyAngles[2];
	Vector m_lobotomyViewAngles[2];
	Vector m_lobotomyVelocity[2];
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureLobotomy.h
#endif //__cplusplus

#endif //CFEATURELOBOTOMY_H_GUARD

#undef CFEATURELOBOTOMY_H_RECURSE_GUARD
#endif //CFEATURELOBOTOMY_H_RECURSE_GUARD