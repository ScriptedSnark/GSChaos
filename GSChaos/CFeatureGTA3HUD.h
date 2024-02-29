/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGTA3HUD.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGTA3HUD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGTA3HUD.h
#else //CFEATUREGTA3HUD_H_RECURSE_GUARD

#define CFEATUREGTA3HUD_H_RECURSE_GUARD

#ifndef CFEATUREGTA3HUD_H_GUARD
#define CFEATUREGTA3HUD_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGTA3HUD : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void OnFrame(double time) override;
	void Draw() override;
private:
	ImFont* m_pArialBlack;
	ImFont* m_pPricedown;
	bool m_bActivated;
	bool m_bFlashHealth;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGTA3HUD.h
#endif //__cplusplus

#endif //CFEATUREGTA3HUD_H_GUARD

#undef CFEATUREGTA3HUD_H_RECURSE_GUARD
#endif //CFEATUREGTA3HUD_H_RECURSE_GUARD