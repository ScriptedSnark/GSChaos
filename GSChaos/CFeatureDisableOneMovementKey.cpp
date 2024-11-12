#include "includes.h"

void CFeatureDisableOneMovementKey::Init()
{
	CChaosFeature::Init();
}

void CFeatureDisableOneMovementKey::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	int index = gChaos.GetRandomValue(0, MAX_KEYS - 1);
	m_bDisabledMovementKeys[index] = true;

	pEngfuncs->Con_Printf("[CFeatureDisableOneMovementKey] Blocking key \"%s\"...\n", GetKeyName());
}

void CFeatureDisableOneMovementKey::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	for (int i = 0; i < MAX_KEYS; i++)
		m_bDisabledMovementKeys[i] = false;
}

void CFeatureDisableOneMovementKey::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	if (!IsActive())
		return;

	if (cmd->forwardmove > 0.0f && m_bDisabledMovementKeys[KEY_FORWARD]) cmd->forwardmove = 0.0f;
	if (cmd->sidemove < 0.0f && m_bDisabledMovementKeys[KEY_LEFT]) cmd->sidemove = 0.0f;
	if (cmd->sidemove > 0.0f && m_bDisabledMovementKeys[KEY_RIGHT]) cmd->sidemove = 0.0f;
	if (cmd->forwardmove < 0.0f && m_bDisabledMovementKeys[KEY_BACK]) cmd->forwardmove = 0.0f;
}

const char* CFeatureDisableOneMovementKey::GetFeatureName()
{
	return "Disable One Movement Key";
}

double CFeatureDisableOneMovementKey::GetDuration()
{
	return gChaos.GetChaosTime() * 1.25;
}

bool CFeatureDisableOneMovementKey::UseCustomDuration()
{
	return true;
}

bool CFeatureDisableOneMovementKey::CanBeInfinite()
{
	return true;
}

const char* CFeatureDisableOneMovementKey::GetKeyName()
{
	if (m_bDisabledMovementKeys[KEY_FORWARD])
		return "W";
	else if (m_bDisabledMovementKeys[KEY_LEFT])
		return "A";
	else if (m_bDisabledMovementKeys[KEY_RIGHT])
		return "D";
	else if (m_bDisabledMovementKeys[KEY_BACK])
		return "S";
	else
		return "NULL";
}