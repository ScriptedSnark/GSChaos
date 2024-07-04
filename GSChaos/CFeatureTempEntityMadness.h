/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureTempEntityMadness.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETEMPENTITYMADNESS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTempEntityMadness.h
#else //CFEATURETEMPENTITYMADNESS_H_RECURSE_GUARD

#define CFEATURETEMPENTITYMADNESS_H_RECURSE_GUARD

#ifndef CFEATURETEMPENTITYMADNESS_H_GUARD
#define CFEATURETEMPENTITYMADNESS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureTempEntityMadness : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	void Restore() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;

	void TE_BeamPoints();
	void TE_Gunshot();
	void TE_Smoke();
	void TE_Tracer();
	void TE_Lightning();
	void TE_Sparks();
	void TE_Implosion();
	void TE_SpriteTrail();
	void TE_Sprite();
	void TE_BeamTorus();
	void TE_DLight();
	void TE_ELight();
	void TE_Line();
	void TE_Box();
	void TE_LargeFunnel();
	void TE_BloodStream();
	void TE_Model();
	void TE_ExplodeModel();
	void TE_BreakModel();
	void TE_SpriteSpray();
	void TE_ArmorRicochet();
	void TE_Bubbles();
	void TE_BubbleTrail();
	void TE_ParticleBurst();
	void TE_FireField();
private:
	double m_flTimeToSpawn;
	short m_BeamSprite;
	short m_FireSprite;
	short m_SmokeSprite;
	short m_ShockwaveSprite;
	short m_LightningSprite;
	short m_GlowSprite;
	short m_RockModel;
	short m_SkullModel;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureTempEntityMadness.h
#endif //__cplusplus

#endif //CFEATURETEMPENTITYMADNESS_H_GUARD

#undef CFEATURETEMPENTITYMADNESS_H_RECURSE_GUARD
#endif //CFEATURETEMPENTITYMADNESS_H_RECURSE_GUARD