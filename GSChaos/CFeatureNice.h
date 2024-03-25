/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureNice.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENICE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNice.h
#else //CFEATURENICE_H_RECURSE_GUARD

#define CFEATURENICE_H_RECURSE_GUARD

#ifndef CFEATURENICE_H_GUARD
#define CFEATURENICE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNice : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNice.h
#endif //__cplusplus

#endif //CFEATURENICE_H_GUARD

#undef CFEATURENICE_H_RECURSE_GUARD
#endif //CFEATURENICE_H_RECURSE_GUARD