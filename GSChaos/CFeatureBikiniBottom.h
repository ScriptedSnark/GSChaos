/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureBikiniBottom.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREBIKINIBOTTOM_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureBikiniBottom.h
#else //CFEATUREBIKINIBOTTOM_H_RECURSE_GUARD

#define CFEATUREBIKINIBOTTOM_H_RECURSE_GUARD

#ifndef CFEATUREBIKINIBOTTOM_H_GUARD
#define CFEATUREBIKINIBOTTOM_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureBikiniBottom : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureBikiniBottom.h
#endif //__cplusplus

#endif //CFEATUREBIKINIBOTTOM_H_GUARD

#undef CFEATUREBIKINIBOTTOM_H_RECURSE_GUARD
#endif //CFEATUREBIKINIBOTTOM_H_RECURSE_GUARD