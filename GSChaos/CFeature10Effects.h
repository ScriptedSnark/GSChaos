/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeature10Effects.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURE10EFFECTS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeature10Effects.h
#else //CFEATURE10EFFECTS_H_RECURSE_GUARD

#define CFEATURE10EFFECTS_H_RECURSE_GUARD

#ifndef CFEATURE10EFFECTS_H_GUARD
#define CFEATURE10EFFECTS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeature10Effects : public CFeatureCombineEffects
{
	const char* GetBaseFeatureName() override;
	int HowManyEffects() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeature10Effects.h
#endif //__cplusplus

#endif //CFEATURE10EFFECTS_H_GUARD

#undef CFEATURE10EFFECTS_H_RECURSE_GUARD
#endif //CFEATURE10EFFECTS_H_RECURSE_GUARD