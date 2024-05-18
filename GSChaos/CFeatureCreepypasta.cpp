#include "includes.h"

void CFeatureCreepypasta::Init()
{
	CChaosFeature::Init();
}

void CFeatureCreepypasta::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureCreepypasta::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureCreepypasta::GetFeatureName()
{
	return "Creepypasta Mode";
}

void CFeatureCreepypasta::SwapBuffers()
{
	int width = ImGui::GetIO().DisplaySize.x;
	int height = ImGui::GetIO().DisplaySize.y;

	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
	glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, 32767);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA8, 0, 0, width, height, 0);

	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1, 1, 0, 0.1, 100);

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, 32767);

	glColor4f(1, 1, 1, 1);

	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_COPY_INVERTED);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 1, -1);
	glTexCoord2f(0, height);
	glVertex3f(0, 0, -1);
	glTexCoord2f(width, height);
	glVertex3f(1, 0, -1);
	glTexCoord2f(width, 0);
	glVertex3f(1, 1, -1);
	glEnd();

	glDisable(GL_COLOR_LOGIC_OP);

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, 32767);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA8, 0, 0, width, height, 0);

	glColor4f(0.6, 0, 0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 1, -1);
	glTexCoord2f(0, height);
	glVertex3f(0, 0, -1);
	glTexCoord2f(width, height);
	glVertex3f(1, 0, -1);
	glTexCoord2f(width, 0);
	glVertex3f(1, 1, -1);
	glEnd();

	// Restore OpenGL states
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_TEXTURE_RECTANGLE_NV);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

double CFeatureCreepypasta::GetDuration()
{
	return gChaos.GetChaosTime() * 0.2;
}

bool CFeatureCreepypasta::UseCustomDuration()
{
	return true;
}