/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureRandomGameSpeed.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURERANDOMGAMESPEED_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureRandomGameSpeed.h
#else //CFEATURERANDOMGAMESPEED_H_RECURSE_GUARD

#define CFEATURERANDOMGAMESPEED_H_RECURSE_GUARD

#ifndef CFEATURERANDOMGAMESPEED_H_GUARD
#define CFEATURERANDOMGAMESPEED_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureRandomGameSpeed : public CFeatureHalfGameSpeed
{
	void ActivateFeature() override;
	const char* GetFeatureName() override;
	float GetTimescale() override;
	double GetDuration() override;
private:
	float m_flGameSpeed;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureRandomGameSpeed.h
#endif //__cplusplus

#endif //CFEATURERANDOMGAMESPEED_H_GUARD

#undef CFEATURERANDOMGAMESPEED_H_RECURSE_GUARD
#endif //CFEATURERANDOMGAMESPEED_H_RECURSE_GUARD