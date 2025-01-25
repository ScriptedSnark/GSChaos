/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureTakeOneHP.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETAKEONEHP_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTakeOneHP.h
#else //CFEATURETAKEONEHP_H_RECURSE_GUARD

#define CFEATURETAKEONEHP_H_RECURSE_GUARD

#ifndef CFEATURETAKEONEHP_H_GUARD
#define CFEATURETAKEONEHP_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureTakeOneHP : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureTakeOneHP.h
#endif //__cplusplus

#endif //CFEATURETAKEONEHP_H_GUARD

#undef CFEATURETAKEONEHP_H_RECURSE_GUARD
#endif //CFEATURETAKEONEHP_H_RECURSE_GUARD