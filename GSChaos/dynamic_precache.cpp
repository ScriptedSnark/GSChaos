#include "includes.h"

_S_LoadSound ORIG_S_LoadSound = NULL;
_S_FindName ORIG_S_FindName = NULL;
_Mod_ForName ORIG_Mod_ForName = NULL;
_PF_precache_model_I ORIG_PF_precache_model_I = NULL;
_PF_precache_sound_I ORIG_PF_precache_sound_I = NULL;
_PF_setmodel_I ORIG_PF_setmodel_I = NULL;
_EV_Precache ORIG_EV_Precache = NULL;
_SV_AddSampleToHashedLookupTable ORIG_SV_AddSampleToHashedLookupTable = NULL;

enum NeedLoad : int
{
	NL_PRESENT = 0,		// The model is already present
	NL_NEEDS_LOADED,	// The model needs to be loaded
	NL_UNREFERENCED		// The model is unreferenced
};

void COM_FixSlashes(char* pname)
{
	for (char* pszNext = pname; *pszNext; ++pszNext)
	{
		if (*pszNext == '\\')
			*pszNext = '/';
	}
}

// By BlueNightHawk (first version of late precache system)
// Will refactor and improve it - ScriptedSnark

int g_ErrorModel = 0;
int iPrecacheCount = 0;

int HOOKED_PF_precache_model_I(char* s)
{
	char* modelname;
	bool bOptional;
	int index;
	const char* currentModel;
	model_t* pModel;

	if (sv->state == ss_loading)
	{
		if (sv->models[0] == nullptr)
			g_ErrorModel = ORIG_PF_precache_model_I("../chaos/error.mdl");

		if (!g_bEncrypted && !g_bPreSteamPipe)
			ORIG_PF_precache_model_I("../chaos/fastrun.bsp");
	}

	modelname = s;
	bOptional = false;

	if (!s)
	{
		pEngfuncs->Con_DPrintf("PF_precache_model_I: NULL pointer \n");
		return g_ErrorModel;
	}

	if (*s <= ' ')
	{
		pEngfuncs->Con_DPrintf("PF_precache_model_I: Bad string '%s' \n", s);
		return g_ErrorModel;
	}

	bOptional = false;
	if (*s == '!')
	{
		modelname = s + 1;
		bOptional = true;
	}

	index = 0;

	while (1)
	{
		currentModel = sv->model_precache[index];

		if (!currentModel)
			break;
		if (!stricmp(currentModel, modelname))
			return index;

		if (++index >= MAX_MODELS)
		{
			pEngfuncs->Con_DPrintf(
				"PF_precache_model_I: Model '%s' failed to precache because the item count is over the %d limit.\n"
				"Reduce the number of brush models and/or regular models in the map to correct this. \n",
				modelname,
				MAX_MODELS);
			return g_ErrorModel;
		}
	}

	pModel = ORIG_Mod_ForName(modelname, false, true);

	if (!pModel)
	{
		pEngfuncs->Con_DPrintf("PF_precache_model_I: Failed to load model %s\n", modelname);
		return 0;
	}

	sv->model_precache[index] = modelname;
	sv->models[index] = pModel;

	if (!bOptional)
		sv->model_precache_flags[index] |= RES_FATALIFMISSING;

	if (sv->state != ss_loading)
	{
		pEngfuncs->Con_DPrintf("PF_precache_model_I: Late Precaching of %s at index: %i \n", modelname, index);
		if (!g_bHL25)
			cl->model_precache[cl->model_precache_count] = sv->models[index];
		else
			cl_hl25->model_precache[cl_hl25->model_precache_count] = sv->models[index];

		//DEBUG_PRINT("cl->model_precache[cl->model_precache_count]->name: %s\n", cl->model_precache[cl->model_precache_count]->name);
		if (!g_bHL25)
			cl->model_precache_count++;
		else
			cl_hl25->model_precache_count++;
	}

	iPrecacheCount = index + 1;

	return index;
}

sfx_t* S_LateLoadSound(char* name)
{
	sfx_t* pSfx = nullptr;

	if (*name == '!' || *name == '*')
		return ORIG_S_FindName(name, nullptr);

	pSfx = ORIG_S_FindName(name, nullptr);

	ORIG_S_LoadSound(pSfx, 0);
	return pSfx;
}

int HOOKED_PF_precache_sound_I(char* s)
{
	int index = 0;
	const char* sound_precache = "";

	if (!s)
	{
		pEngfuncs->Con_DPrintf("PF_precache_sound_I: NULL pointer");
		return 0;
	}
	if (*s <= ' ')
	{
		pEngfuncs->Con_DPrintf("PF_precache_sound_I: Bad string '%s'", s);
		return 0;
	}
	if (*s == '!')
	{
		pEngfuncs->Con_DPrintf("PF_precache_sound_I: '%s' do not precache sentence names!", s);
		return 0;
	}

	// is this used??
	if (sv->state == ss_loading)
		sv->sound_precache_hashedlookup_built = FALSE;

	index = 0;
	while (1)
	{
		sound_precache = sv->sound_precache[index];
		if (!sound_precache)
			break;
		if (!stricmp(sound_precache, s))
			return index;
		if (++index == MAX_SOUNDS)
		{
			pEngfuncs->Con_DPrintf(
				"PF_precache_sound_I: Sound '%s' failed to precache because the item count is over the %d limit.\n"
				"Reduce the number of brush models and/or regular models in the map to correct this.",
				s,
				MAX_SOUNDS);
			return 0;
		}
	}
	sv->sound_precache[index] = s;

	if (sv->state != ss_loading)
	{
		pEngfuncs->Con_DPrintf("PF_precache_sound_I: Late Precaching of %s at index: %i \n", s, index);
		if (!g_bHL25)
			cl->sound_precache[index] = S_LateLoadSound(s);
		else
			cl_hl25->sound_precache[index] = S_LateLoadSound(s);

		if (ORIG_SV_AddSampleToHashedLookupTable)
			ORIG_SV_AddSampleToHashedLookupTable(s, index);
		else
			sv->sound_precache_hashedlookup_built = FALSE;
	}

	return index;
}

void HOOKED_PF_setmodel_I(edict_t* e, const char* m)
{
	if (!HOOKED_PF_precache_model_I((char*)m))
	{
		pEngfuncs->Con_DPrintf("PF_setmodel_I: Could not set model %s \n", m);
		m = "../chaos/error.mdl";
	}

	ORIG_PF_setmodel_I(e, m);
}

unsigned short HOOKED_EV_Precache(int type, const char* psz)
{
	if (!psz)
	{
		pEngfuncs->Con_DPrintf("%s: NULL pointer\n", __func__);
		return 0;
	}

	if (*psz <= 32)
	{
		pEngfuncs->Con_DPrintf("%s: Bad string '%s'\n", __func__, psz);
		return 0;
	}

	if (sv->state != ss_dead)
	{
		for (int i = 1; i < MAX_EVENTS; i++)
		{
			struct event_s* ev = &sv->event_precache[i];
			if (!ev)
				return 0;

			if (!ev->filename)
			{
				if (type != 1)
				{
					pEngfuncs->Con_DPrintf("%s:  only file type 1 supported currently\n", __func__);
					return 0;
				}

				char szpath[MAX_PATH];
				snprintf(szpath, sizeof(szpath), "%s", psz);
				COM_FixSlashes(szpath);

				int scriptSize = 0;
				char* evScript = (char*)pEngfuncs->COM_LoadFile(szpath, 5, &scriptSize);
				if (!evScript)
					pEngfuncs->Con_DPrintf("%s:  file %s missing from server\n", __func__, psz);

				sv->event_precache[i].filename = psz;
				sv->event_precache[i].filesize = scriptSize;
				sv->event_precache[i].pszScript = evScript;
				sv->event_precache[i].index = i;

				if (sv->state == ss_active)
				{
					pEngfuncs->Con_DPrintf("Dynamically precaching %s...\n", psz);
					// crashes
					/*
					event_t* event_precache = CLWrapper::GetEventPrecache();
					event_precache[i].filename = psz;
					event_precache[i].filesize = scriptSize;
					event_precache[i].pszScript = evScript;
					event_precache[i].index = i;
					*/
				}

				return i;
			}

			if (!stricmp(ev->filename, psz))
				return i;
		}

		pEngfuncs->Con_DPrintf("%s: '%s' overflow\n", __func__, psz);
	}
	else
	{
		for (int i = 1; i < MAX_EVENTS; i++)
		{
			struct event_s* ev = &sv->event_precache[i];
			if (!stricmp(ev->filename, psz))
				return i;
		}

		pEngfuncs->Con_DPrintf("%s: '%s' Precache can only be done when server is active/loading", __func__, psz);
		return 0;
	}

	return 0;
}

void PrintEdictInfo()
{
	if (pEngfuncs->Cmd_Argc() <= 1)
	{
		pEngfuncs->Con_Printf("usage:  edict_info <number>\nexample:  edict_info \"31\"\n");
		return;
	}

	edict_t* e = ORIG_EDICT_NUM(atoi(pEngfuncs->Cmd_Argv(1)));
	cl_entity_t* client_e = pEngfuncs->GetEntityByIndex(atoi(pEngfuncs->Cmd_Argv(1)));

	DEBUG_PRINT("SERVER-PART\n");
	DEBUG_PRINT("=================\n");
	DEBUG_PRINT("Edict %i\n", atoi(pEngfuncs->Cmd_Argv(1)));
	DEBUG_PRINT("e->v.model: %s\n", STRING(e->v.model));
	DEBUG_PRINT("e->v.modelindex: %i\n", e->v.modelindex);
	DEBUG_PRINT("=================\n");

	DEBUG_PRINT("\nCLIENT-PART\n");
	DEBUG_PRINT("=================\n");
	DEBUG_PRINT("Edict %i\n", atoi(pEngfuncs->Cmd_Argv(1)));
	DEBUG_PRINT("e->v.model: %s\n", client_e->model->name);
	DEBUG_PRINT("=================\n");
}

void InitDynamicPrecache()
{
	MH_STATUS status;

	SPTFind(S_LoadSound);
	SPTFind(S_FindName);
	SPTFind(Mod_ForName);
	SPTFind(SV_AddSampleToHashedLookupTable);

	if (g_bEncrypted)
		MemUtils::MarkAsExecutable(g_engfuncs->pfnPrecacheModel);

	status = MH_CreateHook(g_engfuncs->pfnPrecacheModel, HOOKED_PF_precache_model_I, reinterpret_cast<void**>(&ORIG_PF_precache_model_I));
	if (status != MH_OK) {
		DEBUG_PRINT("[hw dll] Couldn't create hook for g_engfuncs->pfnPrecacheModel\n");
	}

	if (g_bEncrypted)
		MemUtils::MarkAsExecutable(g_engfuncs->pfnPrecacheSound);

	status = MH_CreateHook(g_engfuncs->pfnPrecacheSound, HOOKED_PF_precache_sound_I, reinterpret_cast<void**>(&ORIG_PF_precache_sound_I));
	if (status != MH_OK) {
		DEBUG_PRINT("[hw dll] Couldn't create hook for g_engfuncs->pfnPrecacheSound.\n");
	}

	if (g_bEncrypted)
		MemUtils::MarkAsExecutable(g_engfuncs->pfnPrecacheEvent);

	status = MH_CreateHook(g_engfuncs->pfnPrecacheEvent, HOOKED_EV_Precache, reinterpret_cast<void**>(&ORIG_EV_Precache));
	if (status != MH_OK) {
		DEBUG_PRINT("[hw dll] Couldn't create hook for g_engfuncs->pfnPrecacheEvent.\n");
	}

	if (g_bEncrypted)
		MemUtils::MarkAsExecutable(g_engfuncs->pfnSetModel);

	status = MH_CreateHook(g_engfuncs->pfnSetModel, HOOKED_PF_setmodel_I, reinterpret_cast<void**>(&ORIG_PF_setmodel_I));
	if (status != MH_OK) {
		DEBUG_PRINT("[hw dll] Couldn't create hook for g_engfuncs->pfnSetModel.\n");
	}

	MH_EnableHook(MH_ALL_HOOKS);

	//pEngfuncs->pfnAddCommand("print_edict", PrintEdictInfo);
}