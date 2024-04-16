#include "includes.h"

typedef void (*_StudioClientEvents)();
_StudioClientEvents ORIG_StudioClientEvents;

CFeatureWideNPCs* g_FeatureWideNPCs;

void HOOKED_StudioClientEvents()
{
	if (g_FeatureWideNPCs && g_FeatureWideNPCs->IsActive())
	{
		g_FeatureWideNPCs->ScaleModel();
	}

	ORIG_StudioClientEvents();
}

void SetCurrentTransformEffect(CFeatureWideNPCs* effect)
{
	g_FeatureWideNPCs = effect;
}

void CFeatureWideNPCs::Init()
{
	CChaosFeature::Init();
	
	static bool bHooked;
	if (!bHooked)
	{
		MH_STATUS status;

		if (g_bEncrypted)
			MemUtils::MarkAsExecutable(engine_studio_api->StudioClientEvents);

		status = MH_CreateHook(engine_studio_api->StudioClientEvents, HOOKED_StudioClientEvents, reinterpret_cast<void**>(&ORIG_StudioClientEvents));
		if (status != MH_OK) {
			DEBUG_PRINT("[hw dll] Couldn't create hook for engine_studio_api->StudioClientEvents\n");
		}

		MH_EnableHook(MH_ALL_HOOKS);

		bHooked = true;
	}
}

void CFeatureWideNPCs::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	SetCurrentTransformEffect(this);

	m_pbonetransform = (float(*)[MAXSTUDIOBONES][3][4])engine_studio_api->StudioGetBoneTransform();

	if (!m_pbonetransform)
		CChaosFeature::DeactivateFeature();
}

void CFeatureWideNPCs::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureWideNPCs::GetFeatureName()
{
	return "Wide NPCs";
}

void CFeatureWideNPCs::ScaleModel()
{
	if (!m_pbonetransform)
		return;

	m_pCurrentEntity = engine_studio_api->GetCurrentEntity();

	m_pRenderModel = m_pCurrentEntity->model;

	m_pStudioHeader = (studiohdr_t*)engine_studio_api->Mod_Extradata(m_pRenderModel);

	for (int i = 0; i < m_pStudioHeader->numbones; i++)
	{
		Transform((*m_pbonetransform)[i]);
	}
}

void CFeatureWideNPCs::Transform(float transform[3][4])
{
	float scale = GetScale();

	transform[1][2] *= scale;
	transform[0][2] *= scale;
}

float CFeatureWideNPCs::GetScale()
{
	return 4.0f;
}

double CFeatureWideNPCs::GetDuration()
{
	return gChaos.GetChaosTime() * 2.0;
}

bool CFeatureWideNPCs::UseCustomDuration()
{
	return true;
}