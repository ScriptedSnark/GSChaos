/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureMakeItBunDem.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMAKEITBUNDEM_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMakeItBunDem.h
#else //CFEATUREMAKEITBUNDEM_H_RECURSE_GUARD

#define CFEATUREMAKEITBUNDEM_H_RECURSE_GUARD

#ifndef CFEATUREMAKEITBUNDEM_H_GUARD
#define CFEATUREMAKEITBUNDEM_H_GUARD
#pragma once

#ifdef __cplusplus

extern int g_flameSpr;

class CFeatureMakeItBunDem : public CChaosFeature
{
	void Burn();
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	bool m_bActivated;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureMakeItBunDem.h
#endif //__cplusplus

#endif //CFEATUREMAKEITBUNDEM_H_GUARD

#undef CFEATUREMAKEITBUNDEM_H_RECURSE_GUARD
#endif //CFEATUREMAKEITBUNDEM_H_RECURSE_GUARD