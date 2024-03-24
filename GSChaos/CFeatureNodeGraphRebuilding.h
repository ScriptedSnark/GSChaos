/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureNodeGraphRebuilding.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENODEGRAPHREBUILDING_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNodeGraphRebuilding.h
#else //CFEATURENODEGRAPHREBUILDING_H_RECURSE_GUARD

#define CFEATURENODEGRAPHREBUILDING_H_RECURSE_GUARD

#ifndef CFEATURENODEGRAPHREBUILDING_H_GUARD
#define CFEATURENODEGRAPHREBUILDING_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNodeGraphRebuilding : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
private:
	double m_flStartTime;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNodeGraphRebuilding.h
#endif //__cplusplus

#endif //CFEATURENODEGRAPHREBUILDING_H_GUARD

#undef CFEATURENODEGRAPHREBUILDING_H_RECURSE_GUARD
#endif //CFEATURENODEGRAPHREBUILDING_H_RECURSE_GUARD