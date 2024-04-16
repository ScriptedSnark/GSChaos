/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureWorstBhopCap.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREWORSTBHOPCAP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureWorstBhopCap.h
#else //CFEATUREWORSTBHOPCAP_H_RECURSE_GUARD

#define CFEATUREWORSTBHOPCAP_H_RECURSE_GUARD

#ifndef CFEATUREWORSTBHOPCAP_H_GUARD
#define CFEATUREWORSTBHOPCAP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureWorstBhopCap : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void PM_Jump() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureWorstBhopCap.h
#endif //__cplusplus

#endif //CFEATUREWORSTBHOPCAP_H_GUARD

#undef CFEATUREWORSTBHOPCAP_H_RECURSE_GUARD
#endif //CFEATUREWORSTBHOPCAP_H_RECURSE_GUARD