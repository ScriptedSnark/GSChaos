/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureOnePercentDeath.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREONEPERCENTDEATH_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureOnePercentDeath.h
#else //CFEATUREONEPERCENTDEATH_H_RECURSE_GUARD

#define CFEATUREONEPERCENTDEATH_H_RECURSE_GUARD

#ifndef CFEATUREONEPERCENTDEATH_H_GUARD
#define CFEATUREONEPERCENTDEATH_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureOnePercentDeath : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureOnePercentDeath.h
#endif //__cplusplus

#endif //CFEATUREONEPERCENTDEATH_H_GUARD

#undef CFEATUREONEPERCENTDEATH_H_RECURSE_GUARD
#endif //CFEATUREONEPERCENTDEATH_H_RECURSE_GUARD