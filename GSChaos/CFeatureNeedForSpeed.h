/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureNeedForSpeed.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURENEEDFORSPEED_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureNeedForSpeed.h
#else //CFEATURENEEDFORSPEED_H_RECURSE_GUARD

#define CFEATURENEEDFORSPEED_H_RECURSE_GUARD

#ifndef CFEATURENEEDFORSPEED_H_GUARD
#define CFEATURENEEDFORSPEED_H_GUARD
#pragma once

#ifdef __cplusplus

#define NFS_REQUIRED_SPEED 320.0f
#define NFS_INIT_FAIL_TIME 1.5
#define NFS_FAIL_TIME 0.35

class CFeatureNeedForSpeed : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	void Draw() override;
	void Explode();
	const char* GetFeatureName() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	bool m_bActivated;
	double m_flTimeToFail;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureNeedForSpeed.h
#endif //__cplusplus

#endif //CFEATURENEEDFORSPEED_H_GUARD

#undef CFEATURENEEDFORSPEED_H_RECURSE_GUARD
#endif //CFEATURENEEDFORSPEED_H_RECURSE_GUARD