/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureInsaneStepsize.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREINSANESTEPSIZE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureInsaneStepsize.h
#else //CFEATUREINSANESTEPSIZE_H_RECURSE_GUARD

#define CFEATUREINSANESTEPSIZE_H_RECURSE_GUARD

#ifndef CFEATUREINSANESTEPSIZE_H_GUARD
#define CFEATUREINSANESTEPSIZE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureInsaneStepsize : public CFeatureNegativeStepsize
{
	const char* GetFeatureName() override;
	float GetStepsizeValue() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureInsaneStepsize.h
#endif //__cplusplus

#endif //CFEATUREINSANESTEPSIZE_H_GUARD

#undef CFEATUREINSANESTEPSIZE_H_RECURSE_GUARD
#endif //CFEATUREINSANESTEPSIZE_H_RECURSE_GUARD