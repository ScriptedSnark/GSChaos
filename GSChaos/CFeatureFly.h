/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureFly.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREFLY_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureFly.h
#else //CFEATUREFLY_H_RECURSE_GUARD

#define CFEATUREFLY_H_RECURSE_GUARD

#ifndef CFEATUREFLY_H_GUARD
#define CFEATUREFLY_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureFly : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureFly.h
#endif //__cplusplus

#endif //CFEATUREFLY_H_GUARD

#undef CFEATUREFLY_H_RECURSE_GUARD
#endif //CFEATUREFLY_H_RECURSE_GUARD