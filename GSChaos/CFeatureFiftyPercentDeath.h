/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureFiftyPercentDeath.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREFIFTYPERCENTDEATH_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureFiftyPercentDeath.h
#else //CFEATUREFIFTYPERCENTDEATH_H_RECURSE_GUARD

#define CFEATUREFIFTYPERCENTDEATH_H_RECURSE_GUARD

#ifndef CFEATUREFIFTYPERCENTDEATH_H_GUARD
#define CFEATUREFIFTYPERCENTDEATH_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureFiftyPercentDeath : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureFiftyPercentDeath.h
#endif //__cplusplus

#endif //CFEATUREFIFTYPERCENTDEATH_H_GUARD

#undef CFEATUREFIFTYPERCENTDEATH_H_RECURSE_GUARD
#endif //CFEATUREFIFTYPERCENTDEATH_H_RECURSE_GUARD