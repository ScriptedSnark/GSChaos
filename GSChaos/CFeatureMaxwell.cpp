#include "includes.h"
#define FRAMECOUNT 86
void CFeatureMaxwell::Init()
{
	CChaosFeature::Init();

	frames = new unsigned char* [FRAMECOUNT];
	// Bit of an ugly way to load but it'll do for now.
	loaded = LoadTexturesFromFiles("chaos/maxwell/maxwell", FRAMECOUNT, frames, &width, &height);
	m_iMaxwellID = TEXTURE_BASEID + ++g_iTextureCounter;
	fps = 15;
}

void CFeatureMaxwell::ActivateFeature()
{
	CFeatureForgotCSS::ActivateFeature();
	textureUpdatingActive = true && loaded;
	ChaosLoud::EmitSound(SND_MAXWELL);
	m_iMaxwellModel = PRECACHE_MODEL(CHAOS_PATH "maxwell/dingus.mdl"); // HACK
}

void CFeatureMaxwell::DeactivateFeature()
{
	ChaosLoud::StopSound(SND_MAXWELL);
	CFeatureForgotCSS::DeactivateFeature();
}
void CFeatureMaxwell::OnFrame(double time)
{
	if (!textureUpdatingActive || !loaded)
		return;

	int newFrame = (int)(pEngfuncs->GetAbsoluteTime() * fps) % FRAMECOUNT;
	if (newFrame != currentFrame)
	{
		UpdateTexture(currentFrame = newFrame);
	}
	CFeatureForgotCSS::OnFrame(time);
}
int CFeatureMaxwell::GetTextureID()
{
	return m_iMaxwellID;
}

void CFeatureMaxwell::HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	if (ent->model->type != mod_studio)
		return;

	if (pEngfuncs->hudGetModelByIndex(m_iMaxwellModel))
		ent->model = pEngfuncs->hudGetModelByIndex(m_iMaxwellModel);
}

void CFeatureMaxwell::Restore()
{
	if (IsActive())
		m_iMaxwellModel = PRECACHE_MODEL(CHAOS_PATH "maxwell/dingus.mdl"); // HACK
	else 
		textureUpdatingActive = false;
}

const char* CFeatureMaxwell::GetFeatureName()
{
	return "Maxwell World";
}

double CFeatureMaxwell::GetDuration()
{
	return gChaos.GetChaosTime() * 1.15;
}

bool CFeatureMaxwell::UseCustomDuration()
{
	return true;
}

bool CFeatureMaxwell::CanBeInfinite()
{
	return true;
}

void CFeatureMaxwell::UpdateTexture(int frameIndex) const
{
	glBindTexture(GL_TEXTURE_2D, m_iMaxwellID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, frames[frameIndex]);

}