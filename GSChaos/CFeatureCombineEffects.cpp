#include "includes.h"

void CFeatureCombineEffects::Init()
{
	CChaosFeature::Init();
}

void CFeatureCombineEffects::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_pszFeatureNames.clear();
	m_sEffectList.clear();
	m_pszEffectList = nullptr;

	static std::random_device randDev;
	std::mt19937 randMT(randDev());

	std::vector<CChaosFeature*> shuffledFeatures = gChaosFeatures;
	std::shuffle(shuffledFeatures.begin(), shuffledFeatures.end(), randMT);

	int effectsNum = HowManyEffects();
	for (int i = 0; i < effectsNum; i++)
	{
		// doing so bad things here
		//yanderedev sim
		if (shuffledFeatures[i] == gChaosFeatures[gChaosFeatures.size() - 1]) // Let's make it more chaotic
		{
			if (shuffledFeatures[i] != this)
				m_pFeatures[i] = shuffledFeatures[15];
		}
		else if (shuffledFeatures[i] == gChaosFeatures[gChaosFeatures.size() - 2]) // Combine effects
		{
			if (shuffledFeatures[i] != this)
				m_pFeatures[i] = shuffledFeatures[12];
		}
		else if (shuffledFeatures[i] == this || strstr(shuffledFeatures[i]->GetFeatureName(), GetBaseFeatureName()))
		{
			if (shuffledFeatures[i] != this)
				m_pFeatures[i] = shuffledFeatures[18]; // pick 17th effect then
		}
		else if (strstr(shuffledFeatures[i]->GetFeatureName(), "New Game :tf:") || strstr(shuffledFeatures[i]->GetFeatureName(), "BSP Dementia"))
		{
			if (shuffledFeatures[i] != this)
				m_pFeatures[i] = shuffledFeatures[gChaos.GetRandomValue(19, (int)(gChaosFeatures.size() - 3))];
		}
		else
		{
			m_pFeatures[i] = shuffledFeatures[i];
		}

		if (!m_pFeatures[i])
			continue;
	
		m_pszFeatureNames.push_back(m_pFeatures[i]->GetFeatureName());
		
		m_pFeatures[i]->ActivateFeature();
		
		DEBUG_PRINT("m_pFeatures[i]->GetFeatureName: %s\n", m_pFeatures[i]->GetFeatureName());
	}

	for (const char* pszFeature : m_pszFeatureNames) {
		m_sEffectList += "\n";
		m_sEffectList += pszFeature;
	}

	m_bActivated = true;
}

void CFeatureCombineEffects::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	int effectsNum = HowManyEffects();
	for (int i = 0; i < effectsNum; i++)
	{
		if (m_pFeatures[i])
			m_pFeatures[i]->DeactivateFeature();
	}

	m_pszFeatureNames.clear();
	m_sEffectList.erase();

	m_pszEffectList = nullptr;
	m_bActivated = false;
}

const char* CFeatureCombineEffects::GetFeatureName()
{
	if (!m_bActivated)
		return GetBaseFeatureName();

	return const_cast<const char*>(UTIL_VarArgs("%s %s", GetBaseFeatureName(), m_sEffectList.c_str()));
}

const char* CFeatureCombineEffects::GetBaseFeatureName()
{
	return "Combine Effects";
}

int CFeatureCombineEffects::HowManyEffects()
{
	return 3;
}