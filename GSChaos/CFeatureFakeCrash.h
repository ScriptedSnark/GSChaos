/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureFakeCrash.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREFAKECRASH_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureFakeCrash.h
#else //CFEATUREFAKECRASH_H_RECURSE_GUARD

#define CFEATUREFAKECRASH_H_RECURSE_GUARD

#ifndef CFEATUREFAKECRASH_H_GUARD
#define CFEATUREFAKECRASH_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureFakeCrash : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
private:
	std::vector<std::string> m_crashMessages;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureFakeCrash.h
#endif //__cplusplus

#endif //CFEATUREFAKECRASH_H_GUARD

#undef CFEATUREFAKECRASH_H_RECURSE_GUARD
#endif //CFEATUREFAKECRASH_H_RECURSE_GUARD