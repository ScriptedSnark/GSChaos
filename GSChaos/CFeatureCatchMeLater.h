/**
 * Copyright - ScriptedSnark, 2025.
 * CFeatureCatchMeLater.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURECATCHMELATER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureCatchMeLater.h
#else //CFEATURECATCHMELATER_H_RECURSE_GUARD

#define CFEATURECATCHMELATER_H_RECURSE_GUARD

#ifndef CFEATURECATCHMELATER_H_GUARD
#define CFEATURECATCHMELATER_H_GUARD

#ifdef _MSC_VER
#pragma once
#endif //_MSC_VER

class CFeatureCatchMeLater : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

extern bool g_bActivatedBarneyBeer;

#endif //CFEATURECATCHMELATER_H_GUARD

#undef CFEATURECATCHMELATER_H_RECURSE_GUARD
#endif //CFEATURECATCHMELATER_H_RECURSE_GUARD