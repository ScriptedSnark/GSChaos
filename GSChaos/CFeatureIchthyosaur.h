/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureIchthyosaur.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREICHTHYOSAUR_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureIchthyosaur.h
#else //CFEATUREICHTHYOSAUR_H_RECURSE_GUARD

#define CFEATUREICHTHYOSAUR_H_RECURSE_GUARD

#ifndef CFEATUREICHTHYOSAUR_H_GUARD
#define CFEATUREICHTHYOSAUR_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureIchthyosaur : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureIchthyosaur.h
#endif //__cplusplus

#endif //CFEATUREICHTHYOSAUR_H_GUARD

#undef CFEATUREICHTHYOSAUR_H_RECURSE_GUARD
#endif //CFEATUREICHTHYOSAUR_H_RECURSE_GUARD