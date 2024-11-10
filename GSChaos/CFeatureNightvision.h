/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureNightvision.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENIGHTVISION_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNightvision.h
#else //CFEATURENIGHTVISION_H_RECURSE_GUARD

#define CFEATURENIGHTVISION_H_RECURSE_GUARD

#ifndef CFEATURENIGHTVISION_H_GUARD
#define CFEATURENIGHTVISION_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNightvision : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void Draw() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
private:
	int m_nvSprite;
	int m_iFrame, m_nFrameCount;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNightvision.h
#endif //__cplusplus

#endif //CFEATURENIGHTVISION_H_GUARD

#undef CFEATURENIGHTVISION_H_RECURSE_GUARD
#endif //CFEATURENIGHTVISION_H_RECURSE_GUARD