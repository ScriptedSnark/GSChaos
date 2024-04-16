/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureMegaJump.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMEGAJUMP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMegaJump.h
#else //CFEATUREMEGAJUMP_H_RECURSE_GUARD

#define CFEATUREMEGAJUMP_H_RECURSE_GUARD

#ifndef CFEATUREMEGAJUMP_H_GUARD
#define CFEATUREMEGAJUMP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureMegaJump : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void PM_Jump() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureMegaJump.h
#endif //__cplusplus

#endif //CFEATUREMEGAJUMP_H_GUARD

#undef CFEATUREMEGAJUMP_H_RECURSE_GUARD
#endif //CFEATUREMEGAJUMP_H_RECURSE_GUARD