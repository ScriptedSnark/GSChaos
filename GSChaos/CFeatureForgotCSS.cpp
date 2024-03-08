#include "includes.h"

typedef void (*_GL_Bind)(int texnum);
_GL_Bind ORIG_GL_Bind = NULL;

texture_t** r_notexture_mip;
int css_texturenum = 0;
bool bBrokenTextures;

void HOOKED_GL_Bind(int texnum)
{
	if (bBrokenTextures)
		texnum = (*r_notexture_mip)->gl_texturenum;

	ORIG_GL_Bind(texnum);
}

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
			}
		});

	/*
	int status;
	SPTFind(GL_Bind);
	CreateHook(GL_Bind);

	MH_EnableHook(MH_ALL_HOOKS);
	*/
}

void CFeatureForgotCSS::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

    bBrokenTextures = true;
    m_bActivated = true;
}

void CFeatureForgotCSS::DeactivateFeature()
{
    CChaosFeature::DeactivateFeature();
    bBrokenTextures = false;
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

int CFeatureForgotCSS::GetTextureID()
{
	return (*r_notexture_mip)->gl_texturenum;
}

const char* CFeatureForgotCSS::GetFeatureName()
{
	return "Forgot to install CS 1.6 :o";
}