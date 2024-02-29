/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureExplosion.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREEXPLOSION_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureExplosion.h
#else //CFEATUREEXPLOSION_H_RECURSE_GUARD

#define CFEATUREEXPLOSION_H_RECURSE_GUARD

#ifndef CFEATUREEXPLOSION_H_GUARD
#define CFEATUREEXPLOSION_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureExplosion : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureExplosion.h
#endif //__cplusplus

#endif //CFEATUREEXPLOSION_H_GUARD

#undef CFEATUREEXPLOSION_H_RECURSE_GUARD
#endif //CFEATUREEXPLOSION_H_RECURSE_GUARD