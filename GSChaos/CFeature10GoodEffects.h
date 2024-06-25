/**
 * Copyright - ScriptedSnark, 2024.
 * CFeature10GoodEffects.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURE10GOODEFFECTS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeature10GoodEffects.h
#else //CFEATURE10GOODEFFECTS_H_RECURSE_GUARD

#define CFEATURE10GOODEFFECTS_H_RECURSE_GUARD

#ifndef CFEATURE10GOODEFFECTS_H_GUARD
#define CFEATURE10GOODEFFECTS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeature10GoodEffects : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeature10GoodEffects.h
#endif //__cplusplus

#endif //CFEATURE10GOODEFFECTS_H_GUARD

#undef CFEATURE10GOODEFFECTS_H_RECURSE_GUARD
#endif //CFEATURE10GOODEFFECTS_H_RECURSE_GUARD