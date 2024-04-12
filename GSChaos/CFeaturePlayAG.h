/**
 * Copyright - ScriptedSnark, 2024.
 * CFeaturePlayAG.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREPLAYAG_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeaturePlayAG.h
#else //CFEATUREPLAYAG_H_RECURSE_GUARD

#define CFEATUREPLAYAG_H_RECURSE_GUARD

#ifndef CFEATUREPLAYAG_H_GUARD
#define CFEATUREPLAYAG_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeaturePlayAG : public CFeatureForgotCSS
{
	void Init() override;
	void ActivateFeature();
	int GetTextureID() override;
	void HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname) override;
	const char* GetFeatureName() override;
private:
	GLuint m_iPlayAGID;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeaturePlayAG.h
#endif //__cplusplus

#endif //CFEATUREPLAYAG_H_GUARD

#undef CFEATUREPLAYAG_H_RECURSE_GUARD
#endif //CFEATUREPLAYAG_H_RECURSE_GUARD