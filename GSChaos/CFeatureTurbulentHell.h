/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureTurbulentHell.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETURBULENTHELL_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTurbulentHell.h
#else //CFEATURETURBULENTHELL_H_RECURSE_GUARD

#define CFEATURETURBULENTHELL_H_RECURSE_GUARD

#ifndef CFEATURETURBULENTHELL_H_GUARD
#define CFEATURETURBULENTHELL_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureTurbulentHell : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
	void R_DrawWorld() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
	bool CanBeInfinite() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureTurbulentHell.h
#endif //__cplusplus

#endif //CFEATURETURBULENTHELL_H_GUARD

#undef CFEATURETURBULENTHELL_H_RECURSE_GUARD
#endif //CFEATURETURBULENTHELL_H_RECURSE_GUARD