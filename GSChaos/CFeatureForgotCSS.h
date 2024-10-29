/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureForgotCSS.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREFORGOTCSS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureForgotCSS.h
#else //CFEATUREFORGOTCSS_H_RECURSE_GUARD

#define CFEATUREFORGOTCSS_H_RECURSE_GUARD

#ifndef CFEATUREFORGOTCSS_H_GUARD
#define CFEATUREFORGOTCSS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureForgotCSS : public CChaosFeature
{
	void Init() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	void HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname) override;
	virtual int GetTextureID();
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
public:
	void ActivateFeature() override;
private:
	bool m_bActivated = false;
	model_t* m_pErrorModel;
	int m_pErrorIndex;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureForgotCSS.h
#endif //__cplusplus

#endif //CFEATUREFORGOTCSS_H_GUARD

#undef CFEATUREFORGOTCSS_H_RECURSE_GUARD
#endif //CFEATUREFORGOTCSS_H_RECURSE_GUARD