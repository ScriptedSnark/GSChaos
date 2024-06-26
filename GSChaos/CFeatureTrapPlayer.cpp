#include "includes.h"

void CFeatureTrapPlayer::Init()
{
	CChaosFeature::Init();
}

void CFeatureTrapPlayer::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureTrapPlayer::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	(*sv_player)->v.flags &= ~FL_FROZEN;

	if (m_pTrap)
		REMOVE_ENTITY(m_pTrap);

	m_pTrap = nullptr;
	m_bTrap = false;
}

void CFeatureTrapPlayer::OnFrame(double time)
{
	if (!IsActive())
		return;

	if (!CLWrapper::GetLevelName()[0])
		return;

	if (!m_bTrap && (*sv_player)->v.flags & FL_ONGROUND && (*sv_player)->v.health > 0.0f)
	{
		m_vOrigin = (*sv_player)->v.origin;
		m_bTrap = true;
	}

	if (m_bTrap)
	{
		if (!m_pTrap)
		{
			m_pTrap = CREATE_NAMED_ENTITY(MAKE_STRING("monster_furniture"));
			if (m_pTrap)
			{
				PRECACHE_MODEL("../chaos/zombie_trap.mdl");
				SET_MODEL(m_pTrap, "../chaos/zombie_trap.mdl");

				gEntityInterface->pfnSpawn(m_pTrap);

				m_pTrap->v.classname = MAKE_STRING("chaos_ztrap");
				m_pTrap->v.origin = (*sv_player)->v.origin - (*sv_player)->v.view_ofs;
				m_pTrap->v.solid = SOLID_NOT;
				m_pTrap->v.flags = 0;

				gEntityInterface->pfnThink(m_pTrap);

				pEngfuncs->pfnClientCmd(";spk ../../chaos/zombi_trapped;\n");

				m_pTrap->v.yaw_speed = 90;
				m_pTrap->v.effects = 0;
				m_pTrap->v.frame = 0;
			}
		}

		(*sv_player)->v.origin = m_vOrigin;
		(*sv_player)->v.velocity = Vector(0, 0, 0);
		(*sv_player)->v.flags |= FL_FROZEN;
	}
	else
		m_flExpireTime = gChaos.GetGlobalTime() + GetDuration();
}

void CFeatureTrapPlayer::Restore()
{
	if (IsActive() && m_flExpireTime != (gChaos.GetGlobalTime() + GetDuration()))
	{
		DeactivateFeature();
	}
}

const char* CFeatureTrapPlayer::GetFeatureName()
{
	return "Trap Player";
}

double CFeatureTrapPlayer::GetDuration()
{
	return 8.0;
}

bool CFeatureTrapPlayer::UseCustomDuration()
{
	return true;
}