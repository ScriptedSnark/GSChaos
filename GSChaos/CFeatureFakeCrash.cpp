#include "includes.h"

void CFeatureFakeCrash::Init()
{
	CChaosFeature::Init();

	m_crashMessages.push_back("NUM_FOR_EDICT: bad pointer");
	m_crashMessages.push_back("Z_Free: freed a pointer without ZONEID");
	m_crashMessages.push_back("EMIT_SOUND: volume = 6996");
	m_crashMessages.push_back("Spawned a NULL entity!");
	m_crashMessages.push_back("PF_MessageEnd_I:  Refusing to send user message Xash2D of 273 bytes to client, user message size limit is 192 bytes");
}

void CFeatureFakeCrash::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	MessageBoxA(NULL, m_crashMessages[gChaos.GetRandomValue(0, m_crashMessages.size() - 1)].c_str(), "Fatal Error", MB_OK);
}

void CFeatureFakeCrash::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureFakeCrash::GetFeatureName()
{
	return "Fake Crash";
}