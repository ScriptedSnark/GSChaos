/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureTotem.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETOTEM_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTotem.h
#else //CFEATURETOTEM_H_RECURSE_GUARD

#define CFEATURETOTEM_H_RECURSE_GUARD

#ifndef CFEATURETOTEM_H_GUARD
#define CFEATURETOTEM_H_GUARD
#pragma once

#ifdef __cplusplus

#define TOTEM_TIME 8.0

class CFeatureTotem : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	void HUD_CreateEntities() override;
	const char* GetFeatureName() override;
	bool IsGood() override;
private:
	bool m_bActivated = false;
	double m_flTotemTime, m_flModelDisappearTime;
	int m_iTotemModelIndex;
};


#else //!__cplusplus
#error C++ compiler required to compile CFeatureTotem.h
#endif //__cplusplus

#endif //CFEATURETOTEM_H_GUARD

#undef CFEATURETOTEM_H_RECURSE_GUARD
#endif //CFEATURETOTEM_H_RECURSE_GUARD