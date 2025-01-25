/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureOhio.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREOHIO_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureOhio.h
#else //CFEATUREOHIO_H_RECURSE_GUARD

#define CFEATUREOHIO_H_RECURSE_GUARD

#ifndef CFEATUREOHIO_H_GUARD
#define CFEATUREOHIO_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureOhio : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	void ResetStates() override;
	double GetDuration() override;
	bool UseCustomDuration() override;
private:
	bool m_bActivated = false;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureOhio.h
#endif //__cplusplus

#endif //CFEATUREOHIO_H_GUARD

#undef CFEATUREOHIO_H_RECURSE_GUARD
#endif //CFEATUREOHIO_H_RECURSE_GUARD