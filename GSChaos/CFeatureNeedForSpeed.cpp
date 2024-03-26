#include "includes.h"

void CFeatureNeedForSpeed::Init()
{
	CChaosFeature::Init();
}

void CFeatureNeedForSpeed::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;

	m_flTimeToFail = gChaos.GetGlobalTime() + NFS_INIT_FAIL_TIME;
}

void CFeatureNeedForSpeed::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;
}

void CFeatureNeedForSpeed::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	Vector velocity = (*sv_player)->v.velocity;
	if (velocity.Length2D() < NFS_REQUIRED_SPEED)
	{
		if (gChaos.GetGlobalTime() > m_flTimeToFail)
		{
			Explode();
			m_bActivated = false;
		}
	}
	else
		m_flTimeToFail = gChaos.GetGlobalTime() + NFS_FAIL_TIME;
}

void CFeatureNeedForSpeed::Draw()
{
	if (!m_bActivated)
		return;

	char buffer[64];
	snprintf(buffer, sizeof(buffer), "%.01f | STAY ABOVE 320 UPS!", (*sv_player)->v.velocity.Length2D());

	ImGui::PushFont(gChaos.m_fontTrebuchet);

	ImVec2 pos = ImVec2((ImGui::GetIO().DisplaySize.x * 0.5f) - (ImGui::CalcTextSize(buffer).x * 0.5f), ImGui::GetIO().DisplaySize.y * 0.1f);
	ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x + 2, pos.y + 2), ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), buffer);
	ImGui::GetForegroundDrawList()->AddText(pos, ImGui::GetColorU32(ImVec4(1.0f, 0.627f, 0.0f, 1.0f)), buffer);

	ImGui::PopFont();
}

void CFeatureNeedForSpeed::Explode() // TODO: make this thing public for every class (move to Utils.cpp)
{
	if (!m_bActivated)
		return;

	// create explosion
	edict_t* pent = CREATE_NAMED_ENTITY(MAKE_STRING("rpg_rocket"));
	if (!pent)
	{
		// heart attack :DDD
		(*sv_player)->v.health = -20;
		return;
	}

	gEntityInterface->pfnSpawn(pent);
	gEntityInterface->pfnThink(pent);

	pent->v.origin = (*sv_player)->v.origin;
	pent->v.angles = (*sv_player)->v.angles;
	pent->v.dmg = 1000;
	pent->v.dmgtime = 1.0f;
	pent->v.nextthink = gpGlobals->time + 0.1f;

	gEntityInterface->pfnTouch((*sv_player), pent);
	gEntityInterface->pfnTouch(pent, (*sv_player));
}

const char* CFeatureNeedForSpeed::GetFeatureName()
{
	return "Need for Speed";
}