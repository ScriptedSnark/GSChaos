#include "includes.h"

typedef void (*_GL_Bind)(int texnum);
_GL_Bind ORIG_GL_Bind = NULL;

texture_t** r_notexture_mip;
int css_texturenum = 0;

void CFeatureForgotCSS::Init()
{
	CChaosFeature::Init();

	void* R_InitTextures;
	auto fR_InitTextures = utils.FindAsync(
		R_InitTextures,
		patterns::engine::R_InitTextures,
		[&](auto pattern) {
			switch (pattern - patterns::engine::R_InitTextures.cbegin())
			{
			default:
			case 0: // HL25
				DEBUG_PRINT("Searching r_notexture_mip in HL25 pattern...\n");
				r_notexture_mip = *reinterpret_cast<texture_t***>(reinterpret_cast<uintptr_t>(R_InitTextures) + 0x19);

				if (r_notexture_mip)
				{
					DEBUG_PRINT("[hw dll] Found r_notexture_mip at 0x%p.\n", r_notexture_mip);
				}

				break;
			case 1: // HL-Steampipe
				DEBUG_PRINT("Searching r_notexture_mip in HL-Steampipe pattern...\n");
				r_notexture_mip = *reinterpret_cast<texture_t***>(reinterpret_cast<uintptr_t>(R_InitTextures) + 0x2F);

				if (r_notexture_mip)
				{
					DEBUG_PRINT("[hw dll] Found r_notexture_mip at 0x%p.\n", r_notexture_mip);
				}

				break;
			case 2: // HL-4554
				DEBUG_PRINT("Searching r_notexture_mip in HL-4554 pattern...\n");
				r_notexture_mip = *reinterpret_cast<texture_t***>(reinterpret_cast<uintptr_t>(R_InitTextures) + 0x2D);

				if (r_notexture_mip)
				{
					DEBUG_PRINT("[hw dll] Found r_notexture_mip at 0x%p.\n", r_notexture_mip);
				}

				break;

			case 3: // CoF-5936
				DEBUG_PRINT("Searching r_notexture_mip in CoF-5936 pattern...\n");
				r_notexture_mip = *reinterpret_cast<texture_t***>(reinterpret_cast<uintptr_t>(R_InitTextures) + 0x19);

				if (r_notexture_mip)
				{
					DEBUG_PRINT("[hw dll] Found r_notexture_mip at 0x%p.\n", r_notexture_mip);
				}

				break;
			}
		});

}

void CFeatureForgotCSS::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

    m_bActivated = true;
}

void CFeatureForgotCSS::DeactivateFeature()
{
    CChaosFeature::DeactivateFeature();
    m_bActivated = false;
}

void CFeatureForgotCSS::OnFrame(double time)
{
    if (!sv->active)
        return;

    if (!m_bActivated)
        return;

    const char* levelName = CLWrapper::GetLevelName();

    if (levelName && levelName[0])
    {
        model_t* worldModel = CLWrapper::GetWorldModel();

        if (!worldModel)
            return;

        for (int i = 0; i < worldModel->numtextures; i++)
        {
            if (worldModel->textures[i])
            {
                worldModel->textures[i]->gl_texturenum = GetTextureID();
            }
        }
    }
}

void CFeatureForgotCSS::HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	if (ent->model->type != mod_studio)
		return;

	if (!m_pErrorModel)
		m_pErrorModel = sv->models[g_ErrorModel];
	
	if (!m_pErrorModel)
		return;

	ent->model = m_pErrorModel;

	ent->prevstate.renderfx = kRenderFxGlowShell;
	ent->prevstate.rendercolor = { 255, 0, 0 };

	ent->curstate.renderfx = kRenderFxGlowShell;
	ent->curstate.rendercolor = { 255, 0, 0};
}

int CFeatureForgotCSS::GetTextureID()
{
	return (*r_notexture_mip)->gl_texturenum;
}

const char* CFeatureForgotCSS::GetFeatureName()
{
	return "Forgot to install CS 1.6 :o";
}

double CFeatureForgotCSS::GetDuration()
{
	return gChaos.GetChaosTime() * 1.2;
}

bool CFeatureForgotCSS::UseCustomDuration()
{
	return true;
}