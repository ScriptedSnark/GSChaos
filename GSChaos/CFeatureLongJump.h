/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureLongJump.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURELONGJUMP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureLongJump.h
#else //CFEATURELONGJUMP_H_RECURSE_GUARD

#define CFEATURELONGJUMP_H_RECURSE_GUARD

#ifndef CFEATURELONGJUMP_H_GUARD
#define CFEATURELONGJUMP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureLongJump : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void PM_Jump() override;
	const char* GetFeatureName() override;
	double GetDuration() override;	
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureLongJump.h
#endif //__cplusplus

#endif //CFEATURELONGJUMP_H_GUARD

#undef CFEATURELONGJUMP_H_RECURSE_GUARD
#endif //CFEATURELONGJUMP_H_RECURSE_GUARD