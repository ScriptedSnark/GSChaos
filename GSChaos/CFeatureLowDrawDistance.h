/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureLowDrawDistance.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURELOWDRAWDISTANCE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureLowDrawDistance.h
#else //CFEATURELOWDRAWDISTANCE_H_RECURSE_GUARD

#define CFEATURELOWDRAWDISTANCE_H_RECURSE_GUARD

#ifndef CFEATURELOWDRAWDISTANCE_H_GUARD
#define CFEATURELOWDRAWDISTANCE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureLowDrawDistance : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
private:
	int m_iOldZMaxValue;
	cvar_t* sv_zmax;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureLowDrawDistance.h
#endif //__cplusplus

#endif //CFEATURELOWDRAWDISTANCE_H_GUARD

#undef CFEATURELOWDRAWDISTANCE_H_RECURSE_GUARD
#endif //CFEATURELOWDRAWDISTANCE_H_RECURSE_GUARD