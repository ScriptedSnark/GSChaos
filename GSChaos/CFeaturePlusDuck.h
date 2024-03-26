/**
 * Copyright - ScriptedSnark, 2024.
 * CFeaturePlusDuck.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREPLUSDUCK_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeaturePlusDuck.h
#else //CFEATUREPLUSDUCK_H_RECURSE_GUARD

#define CFEATUREPLUSDUCK_H_RECURSE_GUARD

#ifndef CFEATUREPLUSDUCK_H_GUARD
#define CFEATUREPLUSDUCK_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeaturePlusDuck : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeaturePlusDuck.h
#endif //__cplusplus

#endif //CFEATUREPLUSDUCK_H_GUARD

#undef CFEATUREPLUSDUCK_H_RECURSE_GUARD
#endif //CFEATUREPLUSDUCK_H_RECURSE_GUARD