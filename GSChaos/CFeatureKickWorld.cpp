#include "includes.h"

void CFeatureKickWorld::Init()
{
	CChaosFeature::Init();
}

void CFeatureKickWorld::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_flKickStartTime = gChaos.GetGlobalTime();
	pEngfuncs->pfnClientCmd(";spk x/x_pain2;\n");
}

void CFeatureKickWorld::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

void CFeatureKickWorld::R_DrawWorld()
{
	float elapsedTime = gChaos.GetGlobalTime() - m_flKickStartTime;

	float translateX = -elapsedTime * 1024.0f;
	float translateY = -elapsedTime * 1024.0f;
	float translateZ = elapsedTime * 1024.0f;
	float rotateAngle = elapsedTime * 720.0f;

	glTranslatef(translateX, translateY, translateZ);

	glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(rotateAngle, 0.0f, 0.0f, 1.0f);
}

const char* CFeatureKickWorld::GetFeatureName()
{
	return "Kick World";
}

double CFeatureKickWorld::GetDuration()
{
	return gChaos.GetChaosTime() * 0.15;
}

bool CFeatureKickWorld::UseCustomDuration()
{
	return true;
}