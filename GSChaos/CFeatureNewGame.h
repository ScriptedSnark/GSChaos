/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureTest.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETEST_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTest.h
#else //CFEATURETEST_H_RECURSE_GUARD

#define CFEATURETEST_H_RECURSE_GUARD

#ifndef CFEATURETEST_H_GUARD
#define CFEATURETEST_H_GUARD
#pragma once

#ifdef __cplusplus

#include "CChaosFeature.h"

class CFeatureNewGame : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
private:
	std::string m_sMapName;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureTest.h
#endif //__cplusplus

#endif //CFEATURETEST_H_GUARD

#undef CFEATURETEST_H_RECURSE_GUARD
#endif //CFEATURETEST_H_RECURSE_GUARD