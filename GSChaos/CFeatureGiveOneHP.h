/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGiveOneHP.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGIVEONEHP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGiveOneHP.h
#else //CFEATUREGIVEONEHP_H_RECURSE_GUARD

#define CFEATUREGIVEONEHP_H_RECURSE_GUARD

#ifndef CFEATUREGIVEONEHP_H_GUARD
#define CFEATUREGIVEONEHP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGiveOneHP : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	bool IsGood() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGiveOneHP.h
#endif //__cplusplus

#endif //CFEATUREGIVEONEHP_H_GUARD

#undef CFEATUREGIVEONEHP_H_RECURSE_GUARD
#endif //CFEATUREGIVEONEHP_H_RECURSE_GUARD