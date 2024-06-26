/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureStandstill.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURESTANDSTILL_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureStandstill.h
#else //CFEATURESTANDSTILL_H_RECURSE_GUARD

#define CFEATURESTANDSTILL_H_RECURSE_GUARD

#ifndef CFEATURESTANDSTILL_H_GUARD
#define CFEATURESTANDSTILL_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureStandstill : public CFeatureHalfGameSpeed
{
	const char* GetFeatureName() override;
	double GetDuration() override;
	float GetTimescale() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureStandstill.h
#endif //__cplusplus

#endif //CFEATURESTANDSTILL_H_GUARD

#undef CFEATURESTANDSTILL_H_RECURSE_GUARD
#endif //CFEATURESTANDSTILL_H_RECURSE_GUARD