/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureCombineEffects.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURECOMBINEEFFECTS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureCombineEffects.h
#else //CFEATURECOMBINEEFFECTS_H_RECURSE_GUARD

#define CFEATURECOMBINEEFFECTS_H_RECURSE_GUARD

#ifndef CFEATURECOMBINEEFFECTS_H_GUARD
#define CFEATURECOMBINEEFFECTS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureCombineEffects : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
private:
	bool m_bActivated;
	CChaosFeature* m_pFeatures[3];
	const char* m_pszEffectList;
	std::string m_sEffectList;
	std::vector<const char*> m_pszFeatureNames;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureCombineEffects.h
#endif //__cplusplus

#endif //CFEATURECOMBINEEFFECTS_H_GUARD

#undef CFEATURECOMBINEEFFECTS_H_RECURSE_GUARD
#endif //CFEATURECOMBINEEFFECTS_H_RECURSE_GUARD