/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGodMode.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGODMODE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGodMode.h
#else //CFEATUREGODMODE_H_RECURSE_GUARD

#define CFEATUREGODMODE_H_RECURSE_GUARD

#ifndef CFEATUREGODMODE_H_GUARD
#define CFEATUREGODMODE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGodMode : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	void ResetStates() override;
private:
	bool m_bActivated;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGodMode.h
#endif //__cplusplus

#endif //CFEATUREGODMODE_H_GUARD

#undef CFEATUREGODMODE_H_RECURSE_GUARD
#endif //CFEATUREGODMODE_H_RECURSE_GUARD