#include "includes.h"

bool g_bActivatedBlur;
constexpr float base_decay = 0.9f;
const float ln_decay = log(base_decay);

void CFeatureBlur::Init()
{
	CChaosFeature::Init();
}

void CFeatureBlur::ActivateFeature()
{
	fps_max = pEngfuncs->pfnGetCvarPointer("fps_max");
	int width = gImGui.m_vecRealDisplaySize.x;
	int height = gImGui.m_vecRealDisplaySize.y;

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, 32766);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA8, 0, 0, width, height, 0);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, 0);

	CChaosFeature::ActivateFeature();
	g_bActivatedBlur = true;
	gChaos.GetRandomValue(0, 1) ? ChaosLoud::EmitSound(SND_BEER1) : ChaosLoud::EmitSound(SND_BEER2);
}

void CFeatureBlur::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	g_bActivatedBlur = false;
}

const char* CFeatureBlur::GetFeatureName()
{
	return "Motion Blur";
}

double CFeatureBlur::GetDuration()
{
	return gChaos.GetChaosTime() * 0.85;
}

bool CFeatureBlur::UseCustomDuration()
{
	return true;
}

void CFeatureBlur::SwapBuffers()
{
	// Makes frames decay out independent of the framerate
	float decay = exp(ln_decay * 100 / fps_max->value);
	// Though blur is a little too weak on lower framerates so I'm reducing the effectiveness of decay
	decay = decay * 0.66667 + 0.3;
	int width = gImGui.m_vecRealDisplaySize.x;
	int height = gImGui.m_vecRealDisplaySize.y;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// bind texture
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, 32766);
	// glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA8, 0, 0, width, height, 0);

	// enable some OpenGL stuff
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glColor4f(1, 1, 1, decay);

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1, 1, 0, 0.1, 100);

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, 32766);

	//glColor4f(1, 1, 1, 1);

	glViewport(0, 0, gImGui.m_vecRealDisplaySize.x, gImGui.m_vecRealDisplaySize.y);

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

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, 32766);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA8, 0, 0, width, height, 0);

	glDisable(GL_TEXTURE_RECTANGLE_NV);
	glEnable(GL_DEPTH_TEST);


	glDisable(GL_BLEND);
}

bool CFeatureBlur::CanBeInfinite()
{
	return true;
}