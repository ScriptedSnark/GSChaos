/**
 * Copyright - ScriptedSnark, 2024.
 * CFeatureTeleportToRandomNPC.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATURETELEPORTTORANDOMNPC_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureTeleportToRandomNPC.h
#else //CFEATURETELEPORTTORANDOMNPC_H_RECURSE_GUARD

#define CFEATURETELEPORTTORANDOMNPC_H_RECURSE_GUARD

#ifndef CFEATURETELEPORTTORANDOMNPC_H_GUARD
#define CFEATURETELEPORTTORANDOMNPC_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureTeleportToRandomNPC : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	const char* GetFeatureName() override;
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureTeleportToRandomNPC.h
#endif //__cplusplus

#endif //CFEATURETELEPORTTORANDOMNPC_H_GUARD

#undef CFEATURETELEPORTTORANDOMNPC_H_RECURSE_GUARD
#endif //CFEATURETELEPORTTORANDOMNPC_H_RECURSE_GUARD