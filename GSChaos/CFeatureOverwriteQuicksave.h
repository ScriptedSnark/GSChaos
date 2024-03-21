/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureOverwriteQuicksave.h 
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREOVERWRITEQUICKSAVE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureOverwriteQuicksave.h
#else //CFEATUREOVERWRITEQUICKSAVE_H_RECURSE_GUARD

#define CFEATUREOVERWRITEQUICKSAVE_H_RECURSE_GUARD

#ifndef CFEATUREOVERWRITEQUICKSAVE_H_GUARD
#define CFEATUREOVERWRITEQUICKSAVE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureOverwriteQuicksave : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureOverwriteQuicksave.h
#endif //__cplusplus

#endif //CFEATUREOVERWRITEQUICKSAVE_H_GUARD

#undef CFEATUREOVERWRITEQUICKSAVE_H_RECURSE_GUARD
#endif //CFEATUREOVERWRITEQUICKSAVE_H_RECURSE_GUARD