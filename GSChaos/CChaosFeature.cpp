#include "includes.h"

std::vector<CChaosFeature*> gChaosFeatures;
std::vector<const char*> gChaosFeaturesNames; // hack

void CChaosFeature::Init()
{
	DEBUG_PRINT("CChaosFeature::Init\n");
}

void CChaosFeature::ActivateFeature()
{
	DEBUG_PRINT("CChaosFeature::ActivateFeature\n");
	DEBUG_PRINT("%s\n", GetFeatureName());

	m_bActivated = true;
	m_flExpireTime = gChaos.GetGlobalTime() + GetDuration();

	if (std::find(gChaos.m_activeFeatures.begin(), gChaos.m_activeFeatures.end(), this) == gChaos.m_activeFeatures.end())
		gChaos.m_activeFeatures.push_back(this);

	if (!m_szPreservedVoterName.empty())
	{
		m_szVoterName = m_szPreservedVoterName;
		m_szPreservedVoterName.clear();
	}
}

void CChaosFeature::DeactivateFeature()
{
	DEBUG_PRINT("CChaosFeature::DeactivateFeature\n");
	m_bActivated = false;

	auto it = std::find(gChaos.m_activeFeatures.begin(), gChaos.m_activeFeatures.end(), this);
	if (it != gChaos.m_activeFeatures.end())
		gChaos.m_activeFeatures.erase(it);

	SetVoterNickname("");
}

void CChaosFeature::OnFrame(double time)
{
	;
}

void CChaosFeature::ExpireThink()
{
	if (!IsActive())
		return;

	if (!UseCustomDuration())
		return;

	if (m_flExpireTime < gChaos.GetGlobalTime())
		DeactivateFeature();
}

const char* CChaosFeature::GetFeatureName()
{
	return "UNDEFINED";
}

void CChaosFeature::Draw()
{
	;
}

void CChaosFeature::ResetStates()
{
	;
}

void CChaosFeature::Restore()
{
	;
}

void CChaosFeature::HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	;
}

void CChaosFeature::SwapBuffers()
{
	;
}

void CChaosFeature::R_DrawWorld()
{
	;
}

void CChaosFeature::PM_Jump()
{
	;
}

void CChaosFeature::Vote(const std::string& user, const std::string& msg)
{

}

bool CChaosFeature::IsActive()
{
	return m_bActivated;
}

double CChaosFeature::GetDuration()
{
	return gChaos.GetChaosTime(); // by default it's 30-45 seconds
}

bool CChaosFeature::UseCustomDuration()
{
	return false;
}

bool CChaosFeature::IsGood()
{
	return false;
}

void CChaosFeature::SetVoterNickname(const std::string& name)
{
	if (IsActive())
		m_szPreservedVoterName = name;
	else
		m_szVoterName = name;
}

const char* CChaosFeature::GetVoterNickname()
{
	return m_szVoterName.c_str();
}