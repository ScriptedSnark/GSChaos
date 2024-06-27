/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureGambling.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGAMBLING_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGambling.h
#else //CFEATUREGAMBLING_H_RECURSE_GUARD

#define CFEATUREGAMBLING_H_RECURSE_GUARD

#ifndef CFEATUREGAMBLING_H_GUARD
#define CFEATUREGAMBLING_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGambling : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
private:
	bool m_bJackpot;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGambling.h
#endif //__cplusplus

#endif //CFEATUREGAMBLING_H_GUARD

#undef CFEATUREGAMBLING_H_RECURSE_GUARD
#endif //CFEATUREGAMBLING_H_RECURSE_GUARD