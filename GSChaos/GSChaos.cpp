/*
* The code in GSChaos can be such a mess, especially OOP.
* It wasn't open-source initially
* so I could do some dolbaeb things inside some implementations. - ScriptedSnark
*/

#include "includes.h"

#ifdef NDEBUG
#undef NDEBUG
#include "assert.h"
#define NDEBUG
#else
#include "assert.h"
#endif

typedef void (*__wassert)(wchar_t const* _Message, wchar_t const* _File, unsigned _Line);
__wassert ORIG_wassert = NULL;

typedef void (*_HUD_Frame)(double time);
typedef int (*_HUD_Redraw)(float time, int intermission);
typedef void (*_V_CalcRefdef)(struct ref_params_s* pparams);
typedef void (*_HUD_CreateEntities)(void);
typedef int (*_HUD_AddEntity)(int type, struct cl_entity_s* ent, const char* modelname);
typedef void (*_CL_CreateMove)(float frametime, struct usercmd_s* cmd, int active);

_HUD_Frame ORIG_HUD_Frame = NULL;
_HUD_Redraw ORIG_HUD_Redraw = NULL;
_V_CalcRefdef ORIG_V_CalcRefdef = NULL;
_HUD_CreateEntities ORIG_HUD_CreateEntities = NULL;
_HUD_AddEntity ORIG_HUD_AddEntity = NULL;
_CL_CreateMove ORIG_CL_CreateMove = NULL;

typedef void (*_LoadThisDll)(char* szDllFilename);
typedef void (*_LoadEntityDLLs)(char* szBaseDir);
typedef void (*_ServerActivate)(edict_t* pEdictList, int edictCount, int clientMax);
typedef void (*_R_DrawWorld)();

#ifdef COF_BUILD
typedef int (*_Host_ValidSave)();
typedef void (*_PlayerPostThink)(edict_t* pEntity);

_Host_ValidSave ORIG_Host_ValidSave = NULL;
_PlayerPostThink ORIG_PlayerPostThink = NULL;
#endif

_LoadThisDll ORIG_LoadThisDll = NULL;
_LoadEntityDLLs ORIG_LoadEntityDLLs = NULL;
_ServerActivate ORIG_ServerActivate = NULL;
_R_DrawWorld ORIG_R_DrawWorld = NULL;

Utils utils = Utils::Utils(NULL, NULL, NULL);

// long pointer to client.dll/opengl32.dll/hw.dll
void* g_lpClient;
void* g_lpOpenGL32;
void* g_lpHW;

// engine funcs
cl_enginefunc_t* pEngfuncs;
enginefuncs_t* g_engfuncs;
globalvars_t* gpGlobals;
DLL_FUNCTIONS* gEntityInterface;
server_t* sv;
client_state_t* cl;
client_state_HL25_t* cl_hl25;
ref_params_t* g_pRefParams;
engine_studio_api_t* engine_studio_api;
float* sys_timescale;

#ifdef COF_BUILD
qboolean* cofSaveHack; // from BunnymodXT
#endif

CChaos gChaos;
CImGuiManager gImGui;

SoLoud::Soloud gSoloud; // SoLoud engine

_wglSwapBuffers ORIG_wglSwapBuffers = NULL;
_WndProc ORIG_WndProc = NULL;

HWND g_hWndOfGame;

std::vector<const char*> g_szExportedWeaponList, g_szExportedEntityList;

bool g_bDrawHUD;
bool g_bHL25 = false;
bool g_bPreSteamPipe = false;

bool g_bEncrypted = false;

bool g_bActivatedShader = false;

extern texture_t** r_notexture_mip;
extern volatile dma_t* shm;

bool g_bOpenWarningWindow = true;

#ifdef COF_BUILD
typedef HMODULE(WINAPI* _LoadLibraryA)(LPCSTR lpLibFileName);
_LoadLibraryA ORIG_LoadLibraryA = NULL;
#endif

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
inline long __stdcall HOOKED_WndProc(const HWND a1, unsigned int a2, unsigned a3, long a4)
{
	ImGui_ImplWin32_WndProcHandler(a1, a2, a3, a4);
	return CallWindowProcA(ORIG_WndProc, a1, a2, a3, a4);
}

void GetExportedMonstersAndWeapons(HMODULE module);

#ifdef COF_BUILD
/*
================
HOOKED_LoadLibraryA
================
*/
HMODULE WINAPI HOOKED_LoadLibraryA(LPCSTR lpLibFileName)
{
	HMODULE hModule = ORIG_LoadLibraryA(lpLibFileName);
	if (hModule)
		DEBUG_PRINT("[WinAPI] Loaded DLL: %s\n", lpLibFileName);
	else
		return hModule;

	if (strstr(lpLibFileName, "hl.dll"))
	{
		GetExportedMonstersAndWeapons(hModule);
	}

	return hModule;
}
#endif
// OPENGL
GLuint program;

_wglSwapBuffers GetSwapBuffersAddr()
{
	return reinterpret_cast<_wglSwapBuffers>(GetProcAddress(LoadLibrary(TEXT("OpenGL32.dll")), "wglSwapBuffers"));
}

int __stdcall HOOKED_wglSwapBuffers(HDC a1)
{
	static bool initialized = false;

	if (!initialized)
	{
		if (FILE* file = fopen("TEMP_chaoswarning", "r"))
		{
			fclose(file);
			g_bOpenWarningWindow = false;
		}
		else
			g_bOpenWarningWindow = true;

		GLenum result = glewInit();
		if (result != GLEW_OK)
		{
			MessageBoxA(NULL, "Failed to initialize GLEW. Exiting...\n", "GSChaos", MB_OK | MB_ICONERROR);
			exit(1);
		}

		HookEngine();
		HookClient();
		MH_EnableHook(MH_ALL_HOOKS);

		g_hWndOfGame = WindowFromDC(a1);

		ORIG_WndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(g_hWndOfGame, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HOOKED_WndProc)));

		gImGui.Init();
		gImGui.InitBackends(g_hWndOfGame);
		gChaos.LoadFonts();

		GLuint fragment = OpenGLShader::CreateFragmentShader("chaos/frag.glsl");
		//GLuint vertex = OpenGLShader::CreateVertexShader("chaos/vertex.glsl");
		program = OpenGLShader::CreateProgram(NULL, fragment);

		initialized = true;
	}

	if (g_bOpenWarningWindow)
	{
		ImGui_ImplWin32_NewFrame();
		ImGui_ImplOpenGL2_NewFrame();
		ImGui::NewFrame();

		// Here you draw...
		// -------------------------

		// Always center this window when appearing
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		ImGui::PushFont(gChaos.m_fontTrebuchet);

		if (ImGui::Begin("GSChaos Warning", nullptr, ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::Text("WARNING! This mod may not be suitable for players suffering from migraine, epilepsy and so on.\nPlay at your own risk!");
			ImGui::Separator();

			if (ImGui::Button("OK", ImVec2(120, 0))) 
			{ 
				FILE* file = fopen("TEMP_chaoswarning", "w");
				fclose(file);

				g_bOpenWarningWindow = false;

			}
			ImGui::SetItemDefaultFocus();

			ImGui::End();
		}

		ImGui::PopFont();

		// -------------------------

		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}

	if (chaos_draw_as_overlay)
	{
		if (chaos_draw_as_overlay->value > 0.0f)
			gImGui.Draw();
	}
	else
		gImGui.Draw();

	for (CChaosFeature* i : gChaosFeatures)
	{
		if (i->IsActive())
			i->SwapBuffers();
	}

	return ORIG_wglSwapBuffers(a1);
}

// CLIENT
qboolean g_FogSkybox, g_FogOn;
float g_FogDensity, g_FogStartDistance, g_FogStopDistance;
float g_FogColor[4], g_FogColorRGB[4];

void InitFog()
{
	g_FogSkybox = TRUE;
	g_FogOn = TRUE;
	g_FogDensity = gChaos.GetRandomValue(7.0f, 16.0f);
	g_FogStartDistance = gChaos.GetRandomValue(0.0f, 500.0f);
	g_FogStopDistance = gChaos.GetRandomValue(2000.0f, 3000.0f);

	for (int i = 0; i < 3; i++)
	{
		g_FogColor[i] = gChaos.GetRandomValue(0.00f, 1.00f);
	}

	g_FogColor[3] = 1.0f;

	for (int i = 0; i < 3; i++)
	{
		g_FogColorRGB[i] = g_FogColor[i] * 255.0f;
	}
}

void RenderFog()
{
	if (g_FogOn == FALSE)
		return;

	pEngfuncs->pTriAPI->FogParams(0.00025f * g_FogDensity, g_FogSkybox);
	pEngfuncs->pTriAPI->Fog(g_FogColorRGB, g_FogStartDistance, g_FogStopDistance, 1);

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, 0.00025f * g_FogDensity);
	glHint(GL_FOG_HINT, GL_NICEST);

	glFogfv(GL_FOG_COLOR, g_FogColor);
	glFogf(GL_FOG_START, g_FogStartDistance);
	glFogf(GL_FOG_END, g_FogStopDistance);
}

void DisableFog()
{
	g_FogOn = FALSE;

	pEngfuncs->pTriAPI->FogParams(0, 0);
	pEngfuncs->pTriAPI->Fog(0, 0, 0, 0);

	glDisable(GL_FOG);
}

void HOOKED_HUD_Frame(double time)
{
	static bool initialized = false;
	if (!initialized)
	{
		gChaos.Init();

		// create a load of blank pixels to create textures with
		unsigned char* pBlankTex = new unsigned char[ImGui::GetIO().DisplaySize.x * ImGui::GetIO().DisplaySize.y * 3];
		memset(pBlankTex, 0, ImGui::GetIO().DisplaySize.x * ImGui::GetIO().DisplaySize.y * 3);

		// Create the SCREEN-HOLDING TEXTURE
		glBindTexture(GL_TEXTURE_RECTANGLE_NV, 32767);

		glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA8, ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y, 0, GL_RGBA8, GL_UNSIGNED_BYTE, 0);

		// free the memory
		delete[] pBlankTex;

		initialized = true;
	}

	ORIG_HUD_Frame(time);
	gChaos.OnFrame(time);
}

int HOOKED_HUD_Redraw(float time, int intermission)
{
	if (chaos_draw_as_overlay && chaos_draw_as_overlay->value <= 0.0f)
		gImGui.Draw();

	return g_bDrawHUD ? 1 : ORIG_HUD_Redraw(time, intermission);
}

void HOOKED_V_CalcRefdef(struct ref_params_s* pparams)
{
	if (g_bActivatedRollin)
	{
		pparams->viewangles[2] += 0.1f;
		pparams->cl_viewangles[2] = pparams->viewangles[2];
	}

	g_pRefParams = pparams;
	ORIG_V_CalcRefdef(pparams);

	if (g_FogSkybox == TRUE)
		RenderFog();
}

void HOOKED_HUD_CreateEntities(void)
{
	for (CChaosFeature* i : gChaosFeatures)
	{
		if (i->IsActive())
			i->HUD_CreateEntities();
	}

	ORIG_HUD_CreateEntities();
}

int HOOKED_HUD_AddEntity(int type, struct cl_entity_s* ent, const char* modelname)
{
	for (CChaosFeature* i : gChaosFeatures)
	{
		if (i->IsActive())
			i->HUD_AddEntity(type, ent, modelname);
	}

	return ORIG_HUD_AddEntity(type, ent, modelname);
}

void HOOKED_CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	ORIG_CL_CreateMove(frametime, cmd, active);

	for (CChaosFeature* i : gChaosFeatures)
	{
		if (i->IsActive())
			i->CL_CreateMove(frametime, cmd, active);
	}
}

// ENGINE
void GetExportedMonstersAndWeapons(HMODULE module)
{
	if (!module)
	{
		DEBUG_PRINT("Invalid module handle\n");
		return;
	}

	PIMAGE_NT_HEADERS ntHeader = ImageNtHeader(module);
	if (!ntHeader)
	{
		DEBUG_PRINT("Failed to get NT headers\n");
		return;
	}
	DWORD exportRva = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	if (!exportRva)
	{
		DEBUG_PRINT("No export table found\n");
		return;
	}

	PIMAGE_EXPORT_DIRECTORY exportDirectory = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(reinterpret_cast<DWORD_PTR>(module) + exportRva);
	DWORD* functionAddresses = reinterpret_cast<DWORD*>(reinterpret_cast<DWORD_PTR>(module) + exportDirectory->AddressOfFunctions);
	DWORD* functionNames = reinterpret_cast<DWORD*>(reinterpret_cast<DWORD_PTR>(module) + exportDirectory->AddressOfNames);
	WORD* nameOrdinals = reinterpret_cast<WORD*>(reinterpret_cast<DWORD_PTR>(module) + exportDirectory->AddressOfNameOrdinals);

	for (DWORD i = 0; i < exportDirectory->NumberOfFunctions; i++)
	{
		DWORD nameRva = functionNames[i];
		const char* functionName = reinterpret_cast<const char*>(reinterpret_cast<DWORD_PTR>(module) + nameRva);
		if (strstr(functionName, "weapon_"))
		{
			DEBUG_PRINT("WEAPON: %s\n", functionName);
			g_szExportedWeaponList.push_back(functionName);
		}
		else if (strstr(functionName, "monster_"))
		{
			DEBUG_PRINT("MONSTER: %s\n", functionName);
			if (strstr(functionName, "furniture") || strstr(functionName, "cine") || strstr(functionName, "repel") || strstr(functionName, "maw") || strstr(functionName, "generic") || strstr(functionName, "mortar") || strstr(functionName, "osprey"))
				continue;

#ifdef COF_BUILD
			if (strstr(functionName, "cof_monster") || strstr(functionName, "boss"))
				continue;
#endif
			g_szExportedEntityList.push_back(functionName);
		}
	}
}

bool IsEntityAvailable(const char* entityName)
{
	if (!entityName)
		return false;

	for (const char* entity : g_szExportedEntityList)
	{
		if (strstr(entity, entityName))
			return true;
		else
			continue;
	}

	return false;
}

void HOOKED_LoadThisDll(char* szDllFilename)
{
	DEBUG_PRINT("LoadThisDll | szDllFilename: %s\n", szDllFilename);
	ORIG_LoadThisDll(szDllFilename);

	HMODULE gameDLL = GetModuleHandle(szDllFilename);
	if (!gameDLL)
	{
		DEBUG_PRINT("Failed to get module handle for Game DLL.\n");
		return;
	}

	g_szExportedEntityList.clear();
	g_szExportedWeaponList.clear();

	GetExportedMonstersAndWeapons(gameDLL);
}

void HOOKED_ServerActivate(edict_t* pEdictList, int edictCount, int clientMax)
{
	ORIG_ServerActivate(pEdictList, edictCount, clientMax);
	gChaos.ResetStates();
}

#ifdef COF_BUILD
void HOOKED_PlayerPostThink(edict_t* pEntity)
{
	bool noclip_set = false;
	if (pEntity && pEntity->pvPrivateData)
	{
		if (pEntity->v.movetype == MOVETYPE_NOCLIP)
			noclip_set = true;
	}

	ORIG_PlayerPostThink(pEntity);

	if (noclip_set)
		pEntity->v.movetype = MOVETYPE_NOCLIP;
}
#endif

void HOOKED_LoadEntityDLLs(char* szBaseDir)
{
	ORIG_LoadEntityDLLs(szBaseDir);

#ifndef COF_BUILD
	int status;

	if (g_bEncrypted)
		MemUtils::MarkAsExecutable(gEntityInterface->pfnPM_Move);

	status = MH_CreateHook(gEntityInterface->pfnPM_Move, HOOKED_PM_Move, reinterpret_cast<void**>(&ORIG_PM_Move));
	if (status != MH_OK) {
		DEBUG_PRINT("[hw dll] Couldn't create hook for gEntityInterface->pfnPM_Move.\n");
	}

	if (g_bEncrypted)
		MemUtils::MarkAsExecutable(gEntityInterface->pfnServerActivate);

	status = MH_CreateHook(gEntityInterface->pfnServerActivate, HOOKED_ServerActivate, reinterpret_cast<void**>(&ORIG_ServerActivate));
	if (status != MH_OK) {
		DEBUG_PRINT("[hw dll] Couldn't create hook for gEntityInterface->pfnServerActivate.\n");
	}

	MH_EnableHook(MH_ALL_HOOKS);
#endif
}

void HOOKED_R_DrawWorld()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	for (CChaosFeature* i : gChaosFeatures)
	{
		if (i->IsActive())
			i->R_DrawWorld();
	}

	if (!g_bActivatedShader)
	{
		ORIG_R_DrawWorld();

		glPopMatrix();

		return;
	}

	glUseProgram(program);
	glUniform2f(glGetUniformLocation(program, "iResolution"), ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);
	glUniform1f(glGetUniformLocation(program, "iTime"), gChaos.GetGlobalTime());

	ORIG_R_DrawWorld();

	glUseProgram(0);

	glPopMatrix();
}

#ifdef COF_BUILD
int HOOKED_Host_ValidSave()
{
	if (cofSaveHack)
		*cofSaveHack = 1;

	return ORIG_Host_ValidSave();
}
#endif

void CAM_Init(void);

void HookClient()
{
	g_lpClient = GetModuleHandle("client.dll");

	if (!g_lpClient)
		return;

	int status;

	Find(Client, HUD_Frame);
	Find(Client, HUD_Redraw);
	Find(Client, V_CalcRefdef);
	Find(Client, HUD_AddEntity);
	Find(Client, CL_CreateMove);
	CreateHook(Client, HUD_Frame);
	CreateHook(Client, HUD_Redraw);
	CreateHook(Client, V_CalcRefdef);
	CreateHook(Client, HUD_AddEntity);
	CreateHook(Client, CL_CreateMove);

	CAM_Init();
}

void HOOKED_wassert(wchar_t const* _Message, wchar_t const* _File, unsigned _Line)
{
	return;
}

void DisableAsserts()
{
	MH_STATUS status = MH_CreateHook(_wassert, HOOKED_wassert, reinterpret_cast<void**>(&ORIG_wassert));

	if (status != MH_OK)
		printf("[WinAPI] Couldn't create hook for _wassert.\n");
	else
		printf("[WinAPI] Detected HL26. Hooked _wassert.\n");

	MH_EnableHook(MH_ALL_HOOKS);
}

void HookEngine()
{
	static void* base;
	static size_t size;

	// now it's broken again so you can't restart the game via engine's _restart (only for build 3248 iirc)
	if (!g_bEncrypted)
	{
		if (!MemUtils::GetModuleInfo(L"hw.dll", &g_lpHW, &base, &size))
		{
			DEBUG_PRINT("HookEngine: can't get module info about hw.dll! Stopping hooking...\n");

			if (MemUtils::GetModuleInfo(L"hl.exe", &g_lpHW, &base, &size))
			{
				g_bEncrypted = true;

				HookEngine();
			}

			return;
		}
	}

	utils = Utils::Utils(g_lpHW, base, size);

	void* ClientDLL_Init;
	auto fClientDLL_Init = utils.FindAsync(
		ClientDLL_Init,
		patterns::engine::ClientDLL_Init,
		[&](auto pattern) {
			switch (pattern - patterns::engine::ClientDLL_Init.cbegin())
			{
			default:
			case 0: // HL-10210
				DEBUG_PRINT("Searching pEngfuncs in HL-10210 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 0x1AB);

				if (pEngfuncs)
					DEBUG_PRINT("[hw dll] Found cl_enginefuncs at 0x%p.\n", pEngfuncs);

				DisableAsserts();

				break;

			case 1: // HL-9920
				DEBUG_PRINT("Searching pEngfuncs in HL-9920 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 0x18B);

				if (pEngfuncs)
					DEBUG_PRINT("[hw dll] Found cl_enginefuncs at 0x%p.\n", pEngfuncs);

				break;
			case 2: // HL-8684
				DEBUG_PRINT("Searching pEngfuncs in HL-8684 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 181);

				if (pEngfuncs)
					DEBUG_PRINT("[hw dll] Found cl_enginefuncs at 0x%p.\n", pEngfuncs);

				break;
			case 3: // HL-4554
				DEBUG_PRINT("Searching pEngfuncs in HL-4554 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 226);

				if (pEngfuncs)
					DEBUG_PRINT("[hw dll] Found cl_enginefuncs at 0x%p.\n", pEngfuncs);

				break;
			case 4: // HL-3248
				DEBUG_PRINT("Searching pEngfuncs in HL-3248 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 203);

				if (pEngfuncs)
					DEBUG_PRINT("[hw dll] Found cl_enginefuncs at 0x%p.\n", pEngfuncs);

				break;
			case 5: // CoF-5936
				DEBUG_PRINT("Searching pEngfuncs in CoF-5936 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 230);

				if (pEngfuncs)
					DEBUG_PRINT("[hw dll] Found cl_enginefuncs at 0x%p.\n", pEngfuncs);

				break;
			}
		});

	void* LoadThisDll;
	auto fLoadThisDll = utils.FindAsync(
		LoadThisDll,
		patterns::engine::LoadThisDll,
		[&](auto pattern) {
			switch (pattern - patterns::engine::LoadThisDll.cbegin())
			{
			default:
			case 0: // HL-9920
				DEBUG_PRINT("Searching g_engfuncs in HL-9920 pattern...\n");
				g_engfuncs = *reinterpret_cast<enginefuncs_t**>(reinterpret_cast<uintptr_t>(LoadThisDll) + 0x5F);
				gpGlobals = *reinterpret_cast<globalvars_t**>(reinterpret_cast<uintptr_t>(LoadThisDll) + 0x5A);

				if (g_engfuncs)
					DEBUG_PRINT("[hw dll] Found g_engfuncs at 0x%p.\n", g_engfuncs);

				if (gpGlobals)
					DEBUG_PRINT("[hw dll] Found gpGlobals at 0x%p.\n", gpGlobals);

				break;
			case 1: // HL-8684
				DEBUG_PRINT("Searching g_engfuncs in HL-8684 pattern...\n");
				g_engfuncs = *reinterpret_cast<enginefuncs_t**>(reinterpret_cast<uintptr_t>(LoadThisDll) + 0x5F);
				gpGlobals = *reinterpret_cast<globalvars_t**>(reinterpret_cast<uintptr_t>(LoadThisDll) + 0x5A);

				if (g_engfuncs)
					DEBUG_PRINT("[hw dll] Found g_engfuncs at 0x%p.\n", g_engfuncs);

				if (gpGlobals)
					DEBUG_PRINT("[hw dll] Found gpGlobals at 0x%p.\n", gpGlobals);
				break;
			case 2: // HL-4554
				DEBUG_PRINT("Searching g_engfuncs in HL-4554 pattern...\n");
				g_engfuncs = *reinterpret_cast<enginefuncs_t**>(reinterpret_cast<uintptr_t>(LoadThisDll) + 91);
				gpGlobals = *reinterpret_cast<globalvars_t**>(reinterpret_cast<uintptr_t>(LoadThisDll) + 86);

				if (g_engfuncs)
					DEBUG_PRINT("[hw dll] Found g_engfuncs at 0x%p.\n", g_engfuncs);

				if (gpGlobals)
					DEBUG_PRINT("[hw dll] Found gpGlobals at 0x%p.\n", gpGlobals);
				break;

			case 3: // CoF-5936
				DEBUG_PRINT("Searching g_engfuncs in CoF-5936 pattern...\n");
				g_engfuncs = *reinterpret_cast<enginefuncs_t**>(reinterpret_cast<uintptr_t>(LoadThisDll) + 118);
				gpGlobals = *reinterpret_cast<globalvars_t**>(reinterpret_cast<uintptr_t>(LoadThisDll) + 113);

				if (g_engfuncs)
					DEBUG_PRINT("[hw dll] Found g_engfuncs at 0x%p.\n", g_engfuncs);

				if (gpGlobals)
					DEBUG_PRINT("[hw dll] Found gpGlobals at 0x%p.\n", gpGlobals);
				break;
			}
		});

	void* LoadEntityDLLs;
	auto fLoadEntityDLLs = utils.FindAsync(
		LoadEntityDLLs,
		patterns::engine::LoadEntityDLLs,
		[&](auto pattern) {
			switch (pattern - patterns::engine::LoadEntityDLLs.cbegin())
			{
			default:
			case 0: // HL-9920
				DEBUG_PRINT("Searching gEntityInterface in HL-9920 pattern...\n");
				gEntityInterface = *reinterpret_cast<DLL_FUNCTIONS**>(reinterpret_cast<uintptr_t>(LoadEntityDLLs) + 0x4CF);

				if (gEntityInterface)
					DEBUG_PRINT("[hw dll] Found gEntityInterface at 0x%p.\n", gEntityInterface);

				break;
			case 1: // HL-8684
				DEBUG_PRINT("Searching gEntityInterface in HL-8684 pattern...\n");
				gEntityInterface = *reinterpret_cast<DLL_FUNCTIONS**>(reinterpret_cast<uintptr_t>(LoadEntityDLLs) + 0x48D);

				if (gEntityInterface)
					DEBUG_PRINT("[hw dll] Found gEntityInterface at 0x%p.\n", gEntityInterface);

				break;
			case 2: // HL-4554
				DEBUG_PRINT("Searching gEntityInterface in HL-4554 pattern...\n");

				if (g_bEncrypted)
					gEntityInterface = *reinterpret_cast<DLL_FUNCTIONS**>(reinterpret_cast<uintptr_t>(LoadEntityDLLs) + 0x35C);
				else
					gEntityInterface = *reinterpret_cast<DLL_FUNCTIONS**>(reinterpret_cast<uintptr_t>(LoadEntityDLLs) + 0x41C);

				if (gEntityInterface)
					DEBUG_PRINT("[hw dll] Found gEntityInterface at 0x%p.\n", gEntityInterface);

				break;

			case 3: // CoF-5936
				DEBUG_PRINT("Searching gEntityInterface in CoF-5936 pattern...\n");

				gEntityInterface = *reinterpret_cast<DLL_FUNCTIONS**>(reinterpret_cast<uintptr_t>(LoadEntityDLLs) + 0x550);

				if (gEntityInterface)
				{
					DEBUG_PRINT("[hw dll] Found gEntityInterface at 0x%p.\n", gEntityInterface);

					int status;

					if (g_bEncrypted)
						MemUtils::MarkAsExecutable(gEntityInterface->pfnPM_Move);

					status = MH_CreateHook(gEntityInterface->pfnPM_Move, HOOKED_PM_Move, reinterpret_cast<void**>(&ORIG_PM_Move));
					if (status != MH_OK) {
						printf("[hw dll] Couldn't create hook for gEntityInterface->pfnPM_Move.\n");
					}

					if (g_bEncrypted)
						MemUtils::MarkAsExecutable(gEntityInterface->pfnServerActivate);

					status = MH_CreateHook(gEntityInterface->pfnServerActivate, HOOKED_ServerActivate, reinterpret_cast<void**>(&ORIG_ServerActivate));
					if (status != MH_OK) {
						printf("[hw dll] Couldn't create hook for gEntityInterface->pfnServerActivate.\n");
					}

#ifdef COF_BUILD
					status = MH_CreateHook(gEntityInterface->pfnPlayerPostThink, HOOKED_PlayerPostThink, reinterpret_cast<void**>(&ORIG_PlayerPostThink));
					if (status != MH_OK) {
						printf("[hw dll] Couldn't create hook for gEntityInterface->pfnPlayerPostThink.\n");
					}
#endif
				}
				break;
			}
		});

	void* Host_ClearMemory;
	auto fHost_ClearMemory = utils.FindAsync(
		Host_ClearMemory,
		patterns::engine::Host_ClearMemory,
		[&](auto pattern) {
			switch (pattern - patterns::engine::Host_ClearMemory.cbegin())
			{
			default:
			case 0: // HL-9920
				DEBUG_PRINT("Searching sv in HL-9920 pattern...\n");
				sv = *reinterpret_cast<server_t**>(reinterpret_cast<uintptr_t>(Host_ClearMemory) + 0xA4);

				if (sv)
				{
					DEBUG_PRINT("[hw dll] Found sv at 0x%p.\n", sv);
				}
				break;
			case 1: // HL-8684
				DEBUG_PRINT("Searching sv in HL-8684 pattern...\n");
				sv = *reinterpret_cast<server_t**>(reinterpret_cast<uintptr_t>(Host_ClearMemory) + 0x5E);
				if (sv)
				{
					DEBUG_PRINT("[hw dll] Found sv at 0x%p.\n", sv);
				}
				break;
			case 2: // HL-4554
				DEBUG_PRINT("Searching sv in HL-4554 pattern...\n");
				sv = *reinterpret_cast<server_t**>(reinterpret_cast<uintptr_t>(Host_ClearMemory) + 0x5C);
				if (sv)
				{
					DEBUG_PRINT("[hw dll] Found sv at 0x%p.\n", sv);
				}
				break;

			case 3: // CoF-5936
				DEBUG_PRINT("Searching sv in CoF-5936 pattern...\n");
				sv = *reinterpret_cast<server_t**>(reinterpret_cast<uintptr_t>(Host_ClearMemory) + 0x5D);
				if (sv)
				{
					DEBUG_PRINT("[hw dll] Found sv at 0x%p.\n", sv);
				}
				break;
			}
		});

	void* CL_Init;
	auto fCL_Init = utils.FindAsync(
		CL_Init,
		patterns::engine::CL_Init,
		[&](auto pattern) {
			switch (pattern - patterns::engine::CL_Init.cbegin())
			{
			default:
			case 0: // HL-9920
				DEBUG_PRINT("Searching cl in HL-9920 pattern...\n");
				cl_hl25 = *reinterpret_cast<client_state_HL25_t**>(reinterpret_cast<uintptr_t>(CL_Init) + 0x52B);

				if (cl_hl25)
				{
					DEBUG_PRINT("[hw dll] Found cl at 0x%p.\n", cl_hl25);
					DEBUG_PRINT("[hw dll] cl->time: %.01f\n", cl_hl25->time);

					g_bHL25 = true;
					g_bPreSteamPipe = false;
				}
				break;
			case 1: // HL-8684
				DEBUG_PRINT("Searching cl in HL-8684 pattern...\n");
				cl = *reinterpret_cast<client_state_t**>(reinterpret_cast<uintptr_t>(CL_Init) + 1);
				if (cl)
				{
					DEBUG_PRINT("[hw dll] Found cl at 0x%p.\n", cl);
					DEBUG_PRINT("[hw dll] cl->time: %.01f\n", cl->time);
					g_bHL25 = false;
					g_bPreSteamPipe = false;
				}
				break;
			case 2: // HL-4554
				DEBUG_PRINT("Searching cl in HL-4554 pattern...\n");
				cl = *reinterpret_cast<client_state_t**>(reinterpret_cast<uintptr_t>(CL_Init) + 1);
				if (cl)
				{
					DEBUG_PRINT("[hw dll] Found cl at 0x%p.\n", cl);
					DEBUG_PRINT("[hw dll] cl->time: %.01f\n", cl->time);
					g_bHL25 = false;
					g_bPreSteamPipe = true;
					DEBUG_PRINT("g_bPreSteamPipe: true\n");
				}
				break;
			case 3: // HL-3248
				DEBUG_PRINT("Searching cl in HL-3248 pattern...\n");
				cl = *reinterpret_cast<client_state_t**>(reinterpret_cast<uintptr_t>(CL_Init) + 1);
				if (cl)
				{
					DEBUG_PRINT("[hw dll] Found cl at 0x%p.\n", cl);
					DEBUG_PRINT("[hw dll] cl->time: %.01f\n", cl->time);
					g_bHL25 = false;
					g_bPreSteamPipe = true;
					DEBUG_PRINT("g_bPreSteamPipe: true\n");
				}
				break;

			case 4: // CoF-5936
				DEBUG_PRINT("Searching cl in CoF-5936 pattern...\n");
				cl = *reinterpret_cast<client_state_t**>(reinterpret_cast<uintptr_t>(CL_Init) + 0x5B8);
				if (cl)
				{
					DEBUG_PRINT("[hw dll] Found cl at 0x%p.\n", cl);
					DEBUG_PRINT("[hw dll] cl->time: %.01f\n", cl->time);
					g_bHL25 = false;
					g_bPreSteamPipe = true;
					DEBUG_PRINT("g_bPreSteamPipe: true\n");
				}
				break;
			}
		});

	void* SNDDMA_InitDirect;
	auto fSNDDMA_InitDirect = utils.FindAsync(
		SNDDMA_InitDirect,
		patterns::engine::SNDDMA_InitDirect,
		[&](auto pattern) {
			switch (pattern - patterns::engine::SNDDMA_InitDirect.cbegin())
			{
			default:
			case 0: // HL-9920
				DEBUG_PRINT("Searching shm in HL-9920 pattern...\n");
				shm = *reinterpret_cast<dma_t**>(reinterpret_cast<uintptr_t>(SNDDMA_InitDirect) + 0x19);

				if (shm)
				{
					DEBUG_PRINT("[hw dll] Found shm at 0x%p.\n", shm);
					DEBUG_PRINT("[hw dll] shm->speed == %i\n", shm->speed);
				}
				break;
			case 1: // HL-8684
				DEBUG_PRINT("Searching shm in HL-8684 pattern...\n");
				shm = *reinterpret_cast<dma_t**>(reinterpret_cast<uintptr_t>(SNDDMA_InitDirect) + 0x46);

				if (shm)
				{
					DEBUG_PRINT("[hw dll] Found shm at 0x%p.\n", shm);
					DEBUG_PRINT("[hw dll] shm->speed == %i\n", shm->speed);
				}
				break;
			case 2: // HL-4554
				DEBUG_PRINT("Searching shm in HL-4554 pattern...\n");
				shm = *reinterpret_cast<dma_t**>(reinterpret_cast<uintptr_t>(SNDDMA_InitDirect) + 0xF);

				if (shm)
				{
					DEBUG_PRINT("[hw dll] Found shm at 0x%p.\n", shm);
					DEBUG_PRINT("[hw dll] shm->speed == %i\n", shm->speed);
				}
				break;

			case 3: // CoF-5936
				DEBUG_PRINT("Searching shm in CoF-5936 pattern...\n");
				shm = *reinterpret_cast<dma_t**>(reinterpret_cast<uintptr_t>(SNDDMA_InitDirect) + 0xE);

				if (shm)
				{
					DEBUG_PRINT("[hw dll] Found shm at 0x%p.\n", shm);
					DEBUG_PRINT("[hw dll] shm->speed == %i\n", shm->speed);
				}
				break;
			}
		});

	void* ClientDLL_HudInit;
	auto fClientDLL_HudInit = utils.FindAsync(
		ClientDLL_HudInit,
		patterns::engine::ClientDLL_HudInit,
		[&](auto pattern) {
			switch (pattern - patterns::engine::ClientDLL_HudInit.cbegin())
			{
			default:
			case 0: // HL-10210
				DEBUG_PRINT("Searching engine_studio_api in HL-10210 pattern...\n");
				engine_studio_api = *reinterpret_cast<engine_studio_api_t**>(reinterpret_cast<uintptr_t>(ClientDLL_HudInit) + 0x4D);

				if (engine_studio_api)
				{
					DEBUG_PRINT("[hw dll] Found engine_studio_api at 0x%p.\n", engine_studio_api);
				}

				break;

			case 1: // HL-9920
				DEBUG_PRINT("Searching engine_studio_api in HL-9920 pattern...\n");
				engine_studio_api = *reinterpret_cast<engine_studio_api_t**>(reinterpret_cast<uintptr_t>(ClientDLL_HudInit) + 0x4D);

				if (engine_studio_api)
				{
					DEBUG_PRINT("[hw dll] Found engine_studio_api at 0x%p.\n", engine_studio_api);
				}

				break;
			case 2: // HL-8684
				DEBUG_PRINT("Searching engine_studio_api in HL-8684 pattern...\n");
				engine_studio_api = *reinterpret_cast<engine_studio_api_t**>(reinterpret_cast<uintptr_t>(ClientDLL_HudInit) + 0x2A);

				if (engine_studio_api)
				{
					DEBUG_PRINT("[hw dll] Found engine_studio_api at 0x%p.\n", engine_studio_api);
				}

				break;
			case 3: // HL-4554
				DEBUG_PRINT("Searching engine_studio_api in HL-4554 pattern...\n");
				engine_studio_api = *reinterpret_cast<engine_studio_api_t**>(reinterpret_cast<uintptr_t>(ClientDLL_HudInit) + 0x28);

				if (engine_studio_api)
				{
					DEBUG_PRINT("[hw dll] Found engine_studio_api at 0x%p.\n", engine_studio_api);
				}

				break;

			case 4: // CoF-5936
				DEBUG_PRINT("Searching engine_studio_api in CoF-5936 pattern...\n");
				engine_studio_api = *reinterpret_cast<engine_studio_api_t**>(reinterpret_cast<uintptr_t>(ClientDLL_HudInit) + 0x30);

				if (engine_studio_api)
				{
					DEBUG_PRINT("[hw dll] Found engine_studio_api at 0x%p.\n", engine_studio_api);
				}

				break;
			}
		});

	void* Host_InitLocal;
	auto fHost_InitLocal = utils.FindAsync(
		Host_InitLocal,
		patterns::engine::Host_InitLocal,
		[&](auto pattern) {
			switch (pattern - patterns::engine::Host_InitLocal.cbegin())
			{
			default:
			case 0: // HL-9920
				DEBUG_PRINT("Searching sys_timescale in HL-9920 pattern...\n");
				sys_timescale = *reinterpret_cast<float**>(reinterpret_cast<uintptr_t>(Host_InitLocal) + 0x10F);

				if (sys_timescale)
				{
					DEBUG_PRINT("[hw dll] Found sys_timescale at 0x%p.\n", sys_timescale);
					DEBUG_PRINT("[hw dll] sys_timescale == %.01f\n", *sys_timescale);
				}
				break;
			case 1: // HL-8684
				DEBUG_PRINT("Searching sys_timescale in HL-8684 pattern...\n");
				sys_timescale = *reinterpret_cast<float**>(reinterpret_cast<uintptr_t>(Host_InitLocal) + 0x48);

				if (sys_timescale)
				{
					DEBUG_PRINT("[hw dll] Found sys_timescale at 0x%p.\n", sys_timescale);
					DEBUG_PRINT("[hw dll] sys_timescale == %.01f\n", *sys_timescale);
				}
				break;
			case 2: // CoF-5936
				DEBUG_PRINT("Searching sys_timescale in CoF-5936 pattern...\n");
				sys_timescale = *reinterpret_cast<float**>(reinterpret_cast<uintptr_t>(Host_InitLocal) + 0x58);

				if (sys_timescale)
				{
					DEBUG_PRINT("[hw dll] Found sys_timescale at 0x%p.\n", sys_timescale);
					DEBUG_PRINT("[hw dll] sys_timescale == %.01f\n", *sys_timescale);
				}
				break;
			}
		});

#ifdef COF_BUILD
	auto fHost_ValidSave = utils.FindAsync(
		ORIG_Host_ValidSave,
		patterns::engine::Host_ValidSave,
		[&](auto pattern) {
			auto f = reinterpret_cast<uintptr_t>(ORIG_Host_ValidSave);
			switch (pattern - patterns::engine::Host_ValidSave.cbegin())
			{
			default:
			case 0: // CoF-5936
				cofSaveHack = *reinterpret_cast<qboolean**>(f + 21);

				if (cofSaveHack)
				{
					*cofSaveHack = TRUE;
				}

				break;
			}
		});
#endif

	int status;

	SPTFind(LoadThisDll);
	SPTFind(LoadEntityDLLs);
	SPTFind(R_DrawWorld);
	EngineCreateHook(LoadThisDll);
	EngineCreateHook(LoadEntityDLLs);
	EngineCreateHook(R_DrawWorld);
#ifdef COF_BUILD
	EngineCreateHook(Host_ValidSave);
#endif

	MH_EnableHook(MH_ALL_HOOKS);
}

void HookOpenGL()
{
	g_lpOpenGL32 = GetModuleHandle("opengl32.dll");

	if (!g_lpOpenGL32)
		return;

	int status;

	ORIG_wglSwapBuffers = GetSwapBuffersAddr();

	Find(OpenGL32, wglSwapBuffers);
	CreateHook(OpenGL32, wglSwapBuffers);

	// also hook WinAPI (CoF)
#ifdef COF_BUILD
	if (MH_CreateHook(&LoadLibraryA, &HOOKED_LoadLibraryA, reinterpret_cast<LPVOID*>(&ORIG_LoadLibraryA)) != MH_OK)
	{
		DEBUG_PRINT("[WinAPI] Couldn't create LoadLibraryA hook.\n");
	}
	else
	{
		DEBUG_PRINT("[WinAPI] Created LoadLibraryA hook.\n");
	}
#endif

	MH_EnableHook(MH_ALL_HOOKS);
}

extern "C" __declspec(dllexport) void ASIMain()
{
	AllocConsole();
	FILE* in, * out;
	freopen_s(&in, "conin$", "r", stdin);
	freopen_s(&out, "conout$", "w+", stdout);

	DEBUG_PRINT("Initializing GSChaos...\n");

	MH_STATUS status = MH_Initialize();

	if (status != MH_OK)
	{
		printf("MH_STATUS: %s\n", MH_StatusToString(status));
		MessageBoxA(NULL, "Failed to initialize MinHook. Exiting...", "GSChaos", MB_OK | MB_ICONERROR);
		exit(1);
		return;
	}

	SoLoud::result result = gSoloud.init();

	if (result != SoLoud::SO_NO_ERROR)
	{
		printf("SoLoud init result: %d\n", result);
		MessageBoxA(NULL, "Failed to initialize SoLoud with MiniAudio backend. Exiting...\n", "GSChaos", MB_OK | MB_ICONERROR);
		exit(1);
		return;
	}

	HookOpenGL();
}

extern "C" __declspec(dllexport) void ASIShutdown()
{
	gChaos.Shutdown();
	gSoloud.deinit();
	MH_Uninitialize();
}