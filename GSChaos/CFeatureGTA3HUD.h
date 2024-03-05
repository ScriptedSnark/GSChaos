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

#define GTA3_HUD_PATH "chaos/hud/"
#define GTAVC_HUD_PATH "chaos/vc_hud/"

// Colors
#define GTA3_HUD_HEALTH_COLOR 186.0f / 255.0f, 101.0f / 255.0f, 50.0f / 255.0f
#define GTA3_HUD_ARMOR_COLOR 124.0f / 255.0f, 140.0f / 255.0f, 95.0f / 255.0f

#define GTAVC_HUD_HEALTH_COLOR 255.0f / 255.0f, 150 / 255.0f, 225 / 255.0f
#define GTAVC_HUD_ARMOR_COLOR 185.0f / 255.0f, 185.0f / 255.0f, 185.0f / 255.0f

// Notify
#define BOX_WIDTH 300.0f
#define BOX_HEIGHT 100.0f
#define DISPLAY_DURATION 2.0f
#define FADE_DURATION 1.0f

class CFeatureGTA3HUD : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void OnFrame(double time) override;
	void Draw() override;
	void Notify(const char* msg);
	void DrawNotify();
private:
	bool m_bActivated;
	bool m_bFlashHealth;
	bool m_bNotificationActive;
	double m_notifyStartTime;
	const char* m_notifyMessage;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGTA3HUD.h
#endif //__cplusplus

#endif //CFEATUREGTA3HUD_H_GUARD

#undef CFEATUREGTA3HUD_H_RECURSE_GUARD
#endif //CFEATUREGTA3HUD_H_RECURSE_GUARD