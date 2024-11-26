/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureMaxwell.h
 *
 * Project (GSChaos) header file
 * Authors: StereoBucket.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMAXWELL_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMaxwell.h
#else //CFEATUREMAXWELL_H_RECURSE_GUARD

#define CFEATUREMAXWELL_H_RECURSE_GUARD

#ifndef CFEATUREMAXWELL_H_GUARD
#define CFEATUREMAXWELL_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureMaxwell : public CFeatureForgotCSS
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	int GetTextureID() override;
	void HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname) override;
	void Restore() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
private:
	void UpdateTexture(int frameIndex) const;
	// Used to keep updating the texture after the effect expires but the texture is present.
	bool textureUpdatingActive = false;
	int width = 0, height = 0;
	double fps;
	int currentFrame = -1;
	int m_iMaxwellModel;
	GLuint m_iMaxwellID;
	unsigned char** frames;
	bool loaded = false;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureMaxwell.h
#endif //__cplusplus

#endif //CFEATUREMAXWELL_H_GUARD

#undef CFEATUREMAXWELL_H_RECURSE_GUARD
#endif //CFEATUREMAXWELL_H_RECURSE_GUARD