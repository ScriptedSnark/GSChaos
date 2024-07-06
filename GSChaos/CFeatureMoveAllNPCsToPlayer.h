/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureMoveAllNPCsToPlayer.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREMOVEALLNPCSTOPLAYER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureMoveAllNPCsToPlayer.h
#else //CFEATUREMOVEALLNPCSTOPLAYER_H_RECURSE_GUARD

#define CFEATUREMOVEALLNPCSTOPLAYER_H_RECURSE_GUARD

#ifndef CFEATUREMOVEALLNPCSTOPLAYER_H_GUARD
#define CFEATUREMOVEALLNPCSTOPLAYER_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureMoveAllNPCsToPlayer : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureMoveAllNPCsToPlayer.h
#endif //__cplusplus

#endif //CFEATUREMOVEALLNPCSTOPLAYER_H_GUARD

#undef CFEATUREMOVEALLNPCSTOPLAYER_H_RECURSE_GUARD
#endif //CFEATUREMOVEALLNPCSTOPLAYER_H_RECURSE_GUARD