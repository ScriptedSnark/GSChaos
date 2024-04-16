/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureWideNPCs.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREWIDENPCS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureWideNPCs.h
#else //CFEATUREWIDENPCS_H_RECURSE_GUARD

#define CFEATUREWIDENPCS_H_RECURSE_GUARD

#ifndef CFEATUREWIDENPCS_H_GUARD
#define CFEATUREWIDENPCS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureWideNPCs : public CChaosFeature
{
public:
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void ScaleModel();
	virtual void Transform(float transform[3][4]);
	virtual float GetScale();
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	cl_entity_t* m_pCurrentEntity;
	model_t* m_pRenderModel;
	studiohdr_t* m_pStudioHeader;
	float(*m_pbonetransform)[MAXSTUDIOBONES][3][4];
};

extern CFeatureWideNPCs* g_FeatureWideNPCs;
void SetCurrentTransformEffect(CFeatureWideNPCs* effect);

#else //!__cplusplus
#error C++ compiler required to compile CFeatureWideNPCs.h
#endif //__cplusplus

#endif //CFEATUREWIDENPCS_H_GUARD

#undef CFEATUREWIDENPCS_H_RECURSE_GUARD
#endif //CFEATUREWIDENPCS_H_RECURSE_GUARD