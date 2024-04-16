/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureAmIDead.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREAMIDEAD_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureAmIDead.h
#else //CFEATUREAMIDEAD_H_RECURSE_GUARD

#define CFEATUREAMIDEAD_H_RECURSE_GUARD

#ifndef CFEATUREAMIDEAD_H_GUARD
#define CFEATUREAMIDEAD_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureAmIDead : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureAmIDead.h
#endif //__cplusplus

#endif //CFEATUREAMIDEAD_H_GUARD

#undef CFEATUREAMIDEAD_H_RECURSE_GUARD
#endif //CFEATUREAMIDEAD_H_RECURSE_GUARD