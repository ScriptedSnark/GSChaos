#include "includes.h"

typedef void (*_S_StartDynamicSound)(int entnum,int entchannel,sfx_t* sfx,vec_t* origin,float fvol,float attenuation,int flags,int pitch);
typedef void (*_S_StartStaticSound)(int entnum, int entchannel, sfx_t* sfx, vec_t* origin, float fvol, float attenuation, int flags, int pitch);
_S_StartDynamicSound ORIG_S_StartDynamicSound = NULL;
_S_StartStaticSound ORIG_S_StartStaticSound = NULL;

int g_iAmmo, g_iClip;
bool g_bActivatedGTA3HUD;

const char* g_szWeaponList[] =
{
	"noweapon",
	"crowbar",
	"9mmhandgun",
	"357",
	"9mmAR",
	"shotgun",
	"crossbow",
	"rpg",
	"gauss",
	"egon",
	"hgun",
	"grenade",
	"satchel",
	"tripmine",
	"squeak"
};

enum {
	WEAPONS = 0,
	CROWBAR,
	GLOCK,
	REVOLVER,
	MP5,
	SHOTGUN,
	CROSSBOW,
	RPG,
	GAUSS,
	EGON,
	HORNETGUN,
	GRENADE,
	SATCHEL,
	TRIPMINE,
	SNARK,
};

struct Weapon
{
	GLuint textureID;
	const char* name;
	int iAmmo;
	int iClip;
};

Weapon g_Weapon[MAX_WEAPONS + 1];
Weapon* g_ActiveWeapon;

GLuint g_iHealthIconID, g_iArmorIconID;

void HOOKED_S_StartDynamicSound(int entnum, int entchannel, sfx_t* sfx, vec_t* origin, float fvol, float attenuation, int flags, int pitch)
{
	//DEBUG_PRINT("[hw.dll] S_StartDynamicSound: %s\n", sfx->name);

	if (g_bHEVMadness)
	{
		if ((sfx->name[0] == '!') && !strstr(sfx->name, "!HEV") && ORIG_EDICT_NUM(entnum) != (*sv_player) && entchannel != CHAN_STATIC)
		{
			int i = gChaos.GetRandomValue(0, g_szHEVSentences.size() - 1);
			strcpy_s(sfx->name, UTIL_VarArgs("!HEV_%s%i", g_szHEVSentences[i], gChaos.GetRandomValue(0, 5)));
			DEBUG_PRINT("sfx->name: %s\n", sfx->name);
		}
		ORIG_S_StartStaticSound(entnum, entchannel, sfx, origin, fvol, attenuation, flags, pitch);
		return;
	}

	if (!g_bActivatedGTA3HUD)
	{
		ORIG_S_StartDynamicSound(entnum, entchannel, sfx, origin, fvol, attenuation, flags, pitch);
		return;
	}

	if (strstr(sfx->name, "items/gunpickup2.wav"))
	{
		ma_engine_set_volume(&miniAudio, CVAR_GET_FLOAT("volume"));
		ma_engine_play_sound(&miniAudio, "chaos/hud/wpn_pickup.wav", NULL);
		return;
	}

	if (strstr(sfx->name, "items/smallmedkit1.wav"))
	{
		ma_engine_set_volume(&miniAudio, CVAR_GET_FLOAT("volume"));
		ma_engine_play_sound(&miniAudio, "chaos/hud/item_pickup.wav", NULL);
		return;
	}

	ORIG_S_StartDynamicSound(entnum, entchannel, sfx, origin, fvol, attenuation, flags, pitch);
}

void HOOKED_S_StartStaticSound(int entnum, int entchannel, sfx_t* sfx, vec_t* origin, float fvol, float attenuation, int flags, int pitch)
{
	//DEBUG_PRINT("[hw.dll] S_StartDynamicSound: %s\n", sfx->name);

	if (!g_bActivatedGTA3HUD)
	{
		ORIG_S_StartStaticSound(entnum, entchannel, sfx, origin, fvol, attenuation, flags, pitch);
		return;
	}

	if (strstr(sfx->name, "!HEV_A1"))
	{
		ma_engine_set_volume(&miniAudio, CVAR_GET_FLOAT("volume"));
		ma_engine_play_sound(&miniAudio, "chaos/hud/item_pickup.wav", NULL);
		return;
	}

	ORIG_S_StartStaticSound(entnum, entchannel, sfx, origin, fvol, attenuation, flags, pitch);
}

void CFeatureGTA3HUD::Init()
{
	CChaosFeature::Init();

	char szPath[MAX_PATH];
	for (int i = 0; i < ARRAYSIZE(g_szWeaponList); i++)
	{
		sprintf(szPath, "chaos/hud/%s.png", g_szWeaponList[i]);
		DEBUG_PRINT("[GTA 3 HUD] Loading %s...\n", szPath);

		g_Weapon[i].name = g_szWeaponList[i];

		if (!LoadTextureFromFile(szPath, &g_Weapon[i].textureID))
			DEBUG_PRINT("[GTA 3 HUD] Failed to load %s!\n", szPath);
	}

	LoadTextureFromFile("chaos/hud/health.png", &g_iHealthIconID);
	LoadTextureFromFile("chaos/hud/armor.png", &g_iArmorIconID);

	int status;
	SPTFind(S_StartDynamicSound);
	SPTFind(S_StartStaticSound);
	CreateHook(S_StartDynamicSound);
	CreateHook(S_StartStaticSound);

	MH_EnableHook(MH_ALL_HOOKS);
}

void CFeatureGTA3HUD::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_bActivated = true;
	g_bActivatedGTA3HUD = true;
	g_bDrawHUD = true;

	ma_engine_set_volume(&miniAudio, CVAR_GET_FLOAT("volume"));
	ma_engine_play_sound(&miniAudio, "chaos/gta3hud.wav", NULL);
}

void CFeatureGTA3HUD::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;
	g_bActivatedGTA3HUD = false;
	g_bDrawHUD = false;
}

void CFeatureGTA3HUD::Draw()
{
	if (!gChaos.IsReady())
		return;

	if (!m_bActivated)
		return;

	if (!g_bHL25)
	{
		if (cl->paused)
			return;
	}
	else
	{
		if (cl_hl25->paused)
			return;
	}

	cl_entity_t* viewmodel = pEngfuncs->GetViewModel();
	char* viewmodelName = viewmodel->model->name;
	bool needSearchWeapon = true;

	if (!viewmodel || !viewmodelName)
	{
		if ((*sv_player)->v.health <= 0)
			return;

		g_ActiveWeapon = &g_Weapon[WEAPONS];
		viewmodelName = const_cast<char*>(g_ActiveWeapon->name);
		needSearchWeapon = false;
	}

	if (needSearchWeapon)
	{
		for (int i = 0; i < ARRAYSIZE(g_szWeaponList); i++)
		{
			if (strstr(viewmodelName, g_Weapon[i].name))
			{
				g_ActiveWeapon = &g_Weapon[i];
				break;
			}
		}
	}

	if (!g_ActiveWeapon)
		return;

	if (!g_ActiveWeapon->textureID)
		return;

	if (!g_ActiveWeapon->name)
		return;

	if ((gChaos.GetFrameCount() & 16) && (*sv_player)->v.health < 10.0f)
		m_bFlashHealth = true;
	else
		m_bFlashHealth = false;

	ImVec2 screenPos = ImVec2(ImGui::GetIO().DisplaySize.x - 384, ImGui::GetIO().DisplaySize.y - (ImGui::GetIO().DisplaySize.y / 1.05f));

	ImGui::SetNextWindowPos(screenPos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - screenPos.x, ImGui::GetIO().DisplaySize.y - screenPos.y), ImGuiCond_Always);
	if (ImGui::Begin("#GTAHUD", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings))
	{
		ImVec2 previousPos, curPos;
		static ImVec2 iconPos = ImVec2(0.0f,0.0f);

		ImGui::Spacing();
		ImGui::Spacing();

		//==========================
		
		// DRAW ARMOR (FOR POSITION)
		ImGui::Image((void*)nullptr, ImVec2(56.0f / 1.75f, 51.0f / 1.75f));

		ImGui::SameLine();
		ImGui::PushFont(m_pPricedown);

		ImGui::TextColored(ImVec4(124.0f / 255.0f, 140.0f / 255.0f, 95.0f / 255.f, 0.0f), "%03d", (int)(*sv_player)->v.armorvalue);

		ImGui::PopFont();

		// DRAW HEALTH (FOR POSITION)
		ImGui::SameLine();

		ImGui::Image((void*)nullptr, ImVec2(64.0f / 1.75f, 55.0f / 1.75f));

		ImGui::SameLine();
		ImGui::PushFont(m_pPricedown);

		ImGui::TextColored(ImVec4(186.0f / 255.0f, 101.0f / 255.0f, 50.0f / 255.0f, 0.0f), "%03d", (int)(*sv_player)->v.health);
		ImGui::PopFont();

		curPos = ImGui::GetCursorPos();

		//==========================

		// DRAW WEAPON ICON

		ImGui::SameLine();
		
		ImVec2 weaponIconPos = ImGui::GetCursorPos();
		ImGui::Image((void*)g_ActiveWeapon->textureID, ImVec2(128, 128));

		iconPos = ImGui::GetCursorPos();

		// DRAW ARMOR
		ImGui::SetCursorPosY(curPos.y + 24.0f);

		if ((*sv_player)->v.armorvalue > 0.0f)
		{
			ImVec2 armorIconPos = ImGui::GetCursorPos();
			// SHADOW
			ImGui::SetCursorPos(ImVec2(armorIconPos.x + 2, armorIconPos.y + 2));
			ImGui::Image((void*)g_iArmorIconID, ImVec2(56.0f / 1.75f, 51.0f / 1.75f), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 1), ImVec4(0, 0, 0, 0));

			// REAL
			ImGui::SetCursorPos(armorIconPos);
			ImGui::Image((void*)g_iArmorIconID, ImVec2(56.0f / 1.75f, 51.0f / 1.75f));
		}
		else
			ImGui::Image((void*)nullptr, ImVec2(56.0f / 1.75f, 51.0f / 1.75f));

		ImGui::SameLine();
		ImGui::PushFont(m_pPricedown);

		if ((*sv_player)->v.armorvalue > 0.0f)
		{
			ImVec2 armorPos = ImGui::GetCursorPos();

			// SHADOW
			ImGui::SetCursorPos(ImVec2(armorPos.x + 2, armorPos.y + 2));
			ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 255.0f / 255.0f), "%03d", (int)(*sv_player)->v.armorvalue);

			// REAL
			ImGui::SetCursorPos(armorPos);
			ImGui::TextColored(ImVec4(124.0f / 255.0f, 140.0f / 255.0f, 95.0f / 255.f, 255.0f / 255.0f), "%03d", (int)(*sv_player)->v.armorvalue);
		}
		else
			ImGui::TextColored(ImVec4(124.0f / 255.0f, 140.0f / 255.0f, 95.0f / 255.f, 0.0f), "%03d", (int)(*sv_player)->v.armorvalue);

		ImGui::PopFont();

		// DRAW HEALTH
		ImGui::SameLine();

		if (m_bFlashHealth)
			ImGui::Image((void*)nullptr, ImVec2(64.0f / 1.75f, 55.0f / 1.75f));
		else
		{
			ImVec2 healthIconPos = ImGui::GetCursorPos();

			// SHADOW
			ImGui::SetCursorPos(ImVec2(healthIconPos.x + 2, healthIconPos.y + 2));
			ImGui::Image((void*)g_iHealthIconID, ImVec2(56.0f / 1.75f, 51.0f / 1.75f), ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 1), ImVec4(0, 0, 0, 0));

			// REAL
			ImGui::SetCursorPos(healthIconPos);
			ImGui::Image((void*)g_iHealthIconID, ImVec2(64.0f / 1.75f, 55.0f / 1.75f));
		}

		ImGui::SameLine();
		ImGui::PushFont(m_pPricedown);

		if (m_bFlashHealth)
		{
			ImGui::TextColored(ImVec4(186.0f / 255.0f, 101.0f / 255.0f, 50.0f / 255.0f, 0.0f), "%03d", (int)(*sv_player)->v.health);
		}
		else
		{
			ImVec2 healthPos = ImGui::GetCursorPos();
			ImGui::SetCursorPos(ImVec2(healthPos.x + 2, healthPos.y + 2));
			ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 255.0f / 255.0f), "%03d", (int)(*sv_player)->v.health);

			ImGui::SetCursorPos(healthPos);
			ImGui::TextColored(ImVec4(186.0f / 255.0f, 101.0f / 255.0f, 50.0f / 255.0f, 255.0f / 255.0f), "%03d", (int)(*sv_player)->v.health);
		}

		ImGui::PopFont();

		// DRAW WEAPON AMMO
		/*
		ImGui::SetCursorPos(ImVec2(weaponIconPos.x + 64, weaponIconPos.y + 96));
		ImGui::PushFont(m_pArialBlack);
		ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "%i/%i", g_ActiveWeapon->iClip, g_ActiveWeapon->iAmmo);
		ImGui::PopFont();
		
		ImGui::GetForegroundDrawList()->AddText(m_pArialBlack, 24.0f, weaponIconPos, ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)),  UTIL_VarArgs("%i/%i", g_ActiveWeapon->iClip, g_ActiveWeapon->iAmmo));
		*/
		ImGui::End();
		//ImGui::GetWindowDrawList()->AddImage((void*)g_ActiveWeapon->textureID, ImVec2(0.0f, 0.0f), ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImVec2(0, 0), ImVec2(1, 1));
	}
}

void CFeatureGTA3HUD::OnFrame(double time)
{
	if (!m_bActivated)
		return;
}

const char* CFeatureGTA3HUD::GetFeatureName()
{
	return "GTA 3 HUD";
}