#include "includes.h"

// HACKS HACKS HACKS HACKS HACKS HACKS HAAAAAAAX!!!!!

typedef void (*_R_DrawViewModel)();
_R_DrawViewModel ORIG_R_DrawViewModel = NULL;

int g_iModelIndex;
extern bool g_bActivatedScreamer;
bool g_bActivatedTotem;
double g_flModelDisappearTime;
double oldWeapontime;

void HOOKED_R_DrawViewModel()
{
	if (!g_bActivatedTotem && !g_bActivatedScreamer)
	{
		ORIG_R_DrawViewModel();
		return;
	}
	
	char* modelName = g_bActivatedTotem ? CHAOS_PATH "v_totem.mdl" : CHAOS_PATH "screamer1.mdl";
	g_iModelIndex = PRECACHE_MODEL(modelName); // we're doing baddest hacks here... - ScriptedSnark
	cl_entity_t* viewent = CLWrapper::GetViewent();

	model_t* oldMod = viewent->model;

	if (!g_bActivatedScreamer)
	{
		ORIG_R_DrawViewModel();

		viewent->model = pEngfuncs->hudGetModelByIndex(g_iModelIndex);

		ORIG_R_DrawViewModel();

		viewent->model = oldMod;
	}
	else
	{
		viewent->model = pEngfuncs->hudGetModelByIndex(g_iModelIndex);
		ORIG_R_DrawViewModel();
	}
	if (g_flModelDisappearTime < gChaos.GetGlobalTime() && (*sv_player) && CLWrapper::GetWorldModel() && !g_bActivatedScreamer)
	{
		UTIL_MakeVectors((*sv_player)->v.angles);
		Vector origin = (*sv_player)->v.origin + (*sv_player)->v.view_ofs + gpGlobals->v_forward * 16;
		MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
		WRITE_BYTE(TE_TELEPORT);
		WRITE_COORD(origin.x);
		WRITE_COORD(origin.y);
		WRITE_COORD(origin.z);
		MESSAGE_END();

		g_bActivatedTotem = false;
	}
}

void CFeatureTotem::Init()
{
	CChaosFeature::Init();

	int status;
	SPTFind(R_DrawViewModel);
	EngineCreateHook(R_DrawViewModel);

	MH_EnableHook(MH_ALL_HOOKS);
}

void CFeatureTotem::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	g_bActivatedTotem = true;
	m_flTotemTime = gChaos.GetGlobalTime() + TOTEM_TIME;
	m_flModelDisappearTime = gChaos.GetGlobalTime() + 2.86;
	g_flModelDisappearTime = m_flModelDisappearTime;
	m_bActivated = true;

	pEngfuncs->pfnWeaponAnim(0, 0);

	ChaosLoud::EmitSound(SND_TOTEM);
}

void CFeatureTotem::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (m_flTotemTime > gChaos.GetGlobalTime())
	{	
		int weaponsequence = cl_hl25 ? cl_hl25->weaponsequence : cl->weaponsequence;
		float& weapontime = cl_hl25 ? cl_hl25->weaponstarttime : cl->weaponstarttime;
		if (g_bActivatedTotem)
		{
			if (weaponsequence != 0)
				weapontime = oldWeapontime;
			else
				oldWeapontime = weapontime;
		}

		(*sv_player)->v.health += 0.15f;
		(*sv_player)->v.armorvalue += 0.02f;
		(*sv_player)->v.flags |= FL_GODMODE;
		Vector origin = (*sv_player)->v.origin;
		origin.z += 20.f;

		PARTICLE_EFFECT(origin, Vector(0, 0, 0), 245, gChaos.GetRandomValue(10, 35));
	}
	else
		DeactivateFeature();
}

void CFeatureTotem::HUD_CreateEntities()
{
}

void CFeatureTotem::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	(*sv_player)->v.health = (int)(*sv_player)->v.health;
	(*sv_player)->v.flags &= ~FL_GODMODE;
	m_bActivated = false;
	g_bActivatedTotem = false;
}

const char* CFeatureTotem::GetFeatureName()
{
	return "Totem of Undying";
}

bool CFeatureTotem::IsGood()
{
	return true;
}