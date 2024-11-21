#include "includes.h"

bool g_bActivatedWideScreen;

void CFeatureWideScreen::Init()
{
	CChaosFeature::Init();
}

void CFeatureWideScreen::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	g_bActivatedWideScreen = true;
}

void CFeatureWideScreen::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedWideScreen = false;
}

const char* CFeatureWideScreen::GetFeatureName()
{
	return "\"It's easier to aim\", they said";
}

double CFeatureWideScreen::GetDuration()
{
	return gChaos.GetChaosTime() * 1.08;
}

bool CFeatureWideScreen::UseCustomDuration()
{
	return true;
}

void CFeatureWideScreen::SwapBuffers()
{
	int width = gImGui.m_vecRealDisplaySize.x;
	int height = gImGui.m_vecRealDisplaySize.y;

	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
	glEnable(GL_BLEND);

	// bind texture
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, 32767);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA8, 0, 0, width, height, 0);

	// enable some OpenGL stuff
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glColor3f(1, 1, 1);
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

	glViewport(0, 0, gImGui.m_vecRealDisplaySize.x, gImGui.m_vecRealDisplaySize.y);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(0, height);
	glVertex3f(-1, 0, -1);
	glTexCoord2f(width, height);
	glVertex3f(2, 0, -1);
	glTexCoord2f(width, 0);
	glVertex3f(2, 1, -1);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_TEXTURE_RECTANGLE_NV);
	glEnable(GL_DEPTH_TEST);


	glDisable(GL_BLEND);
}

bool CFeatureWideScreen::CanBeInfinite()
{
	return true;
}