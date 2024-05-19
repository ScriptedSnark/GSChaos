/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureHigh.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREHIGH_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureHigh.h
#else //CFEATUREHIGH_H_RECURSE_GUARD

#define CFEATUREHIGH_H_RECURSE_GUARD

#ifndef CFEATUREHIGH_H_GUARD
#define CFEATUREHIGH_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureHigh : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	bool m_bDetectedEngineShaders;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureHigh.h
#endif //__cplusplus

#endif //CFEATUREHIGH_H_GUARD

#undef CFEATUREHIGH_H_RECURSE_GUARD
#endif //CFEATUREHIGH_H_RECURSE_GUARD