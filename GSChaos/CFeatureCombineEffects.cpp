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

	for (int i = 0; i < 3; i++)
	{
		//yanderedev sim
		if (shuffledFeatures[i] == this)
			m_pFeatures[i] = shuffledFeatures[9]; // pick 10th effect then
		else
			m_pFeatures[i] = shuffledFeatures[i];

		if (strstr(m_pFeatures[i]->GetFeatureName(), "Fake Crash"))
		{
			m_pFeatures[i] = shuffledFeatures[gChaos.GetRandomValue(20, 29)];

			if (strstr(m_pFeatures[i]->GetFeatureName(), "Fake Crash") || strstr(m_pFeatures[i]->GetFeatureName(), "New Game :tf:"))
				m_pFeatures[i] = gChaosFeatures[10]; // totem
		}

		if (strstr(m_pFeatures[i]->GetFeatureName(), "New Game :tf:"))
		{
			m_pFeatures[i] = shuffledFeatures[gChaos.GetRandomValue(10, 19)];

			if (strstr(m_pFeatures[i]->GetFeatureName(), "Fake Crash") || strstr(m_pFeatures[i]->GetFeatureName(), "New Game :tf:"))
				m_pFeatures[i] = gChaosFeatures[10]; // totem (X2)
		}

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

	for (int i = 0; i < 3; i++)
	{
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
		return "Combine Effects";

	return const_cast<const char*>(UTIL_VarArgs("Combine Effects %s", m_sEffectList.c_str()));
}