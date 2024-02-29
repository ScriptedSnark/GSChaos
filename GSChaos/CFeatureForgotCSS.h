/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureForgotCSS.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREFORGOTCSS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureForgotCSS.h
#else //CFEATUREFORGOTCSS_H_RECURSE_GUARD

#define CFEATUREFORGOTCSS_H_RECURSE_GUARD

#ifndef CFEATUREFORGOTCSS_H_GUARD
#define CFEATUREFORGOTCSS_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureForgotCSS : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;

private:
	bool m_bActivated = false;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureForgotCSS.h
#endif //__cplusplus

#endif //CFEATUREFORGOTCSS_H_GUARD

#undef CFEATUREFORGOTCSS_H_RECURSE_GUARD
#endif //CFEATUREFORGOTCSS_H_RECURSE_GUARD