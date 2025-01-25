/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureNPCExplode.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENPCEXPLODE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNPCExplode.h
#else //CFEATURENPCEXPLODE_H_RECURSE_GUARD

#define CFEATURENPCEXPLODE_H_RECURSE_GUARD

#ifndef CFEATURENPCEXPLODE_H_GUARD
#define CFEATURENPCEXPLODE_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureNPCExplode : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
private:
	int m_iExplosionCount;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNPCExplode.h
#endif //__cplusplus

#endif //CFEATURENPCEXPLODE_H_GUARD

#undef CFEATURENPCEXPLODE_H_RECURSE_GUARD
#endif //CFEATURENPCEXPLODE_H_RECURSE_GUARD