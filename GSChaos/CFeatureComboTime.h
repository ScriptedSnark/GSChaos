/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureComboTime.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURECOMBOTIME_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureComboTime.h
#else //CFEATURECOMBOTIME_H_RECURSE_GUARD

#define CFEATURECOMBOTIME_H_RECURSE_GUARD

#ifndef CFEATURECOMBOTIME_H_GUARD
#define CFEATURECOMBOTIME_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureComboTime : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureComboTime.h
#endif //__cplusplus

#endif //CFEATURECOMBOTIME_H_GUARD

#undef CFEATURECOMBOTIME_H_RECURSE_GUARD
#endif //CFEATURECOMBOTIME_H_RECURSE_GUARD