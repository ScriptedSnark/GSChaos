/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureSlap.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESLAP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureSlap.h
#else //CFEATURESLAP_H_RECURSE_GUARD

#define CFEATURESLAP_H_RECURSE_GUARD

#ifndef CFEATURESLAP_H_GUARD
#define CFEATURESLAP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureSlap : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureSlap.h
#endif //__cplusplus

#endif //CFEATURESLAP_H_GUARD

#undef CFEATURESLAP_H_RECURSE_GUARD
#endif //CFEATURESLAP_H_RECURSE_GUARD