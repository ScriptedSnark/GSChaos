/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureNuke.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENUKE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNuke.h
#else //CFEATURENUKE_H_RECURSE_GUARD

#define CFEATURENUKE_H_RECURSE_GUARD

#ifndef CFEATURENUKE_H_GUARD
#define CFEATURENUKE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNuke : public CChaosFeature
{
	void Nuke();

	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
private:
	double m_flTimeToExplode;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNuke.h
#endif //__cplusplus

#endif //CFEATURENUKE_H_GUARD

#undef CFEATURENUKE_H_RECURSE_GUARD
#endif //CFEATURENUKE_H_RECURSE_GUARD