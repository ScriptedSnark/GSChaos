/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureNoclip.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENOCLIP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNoclip.h
#else //CFEATURENOCLIP_H_RECURSE_GUARD

#define CFEATURENOCLIP_H_RECURSE_GUARD

#ifndef CFEATURENOCLIP_H_GUARD
#define CFEATURENOCLIP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNoclip : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void ResetStates() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNoclip.h
#endif //__cplusplus

#endif //CFEATURENOCLIP_H_GUARD

#undef CFEATURENOCLIP_H_RECURSE_GUARD
#endif //CFEATURENOCLIP_H_RECURSE_GUARD