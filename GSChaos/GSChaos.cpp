/*
* The code in GSChaos can be such a mess, especially OOP.
* It wasn't open-source initially
* so I could do some dolbaeb things inside some implementations. - ScriptedSnark
*/

#include "includes.h"

typedef void (*_HUD_Frame)(double time);
typedef int (*_HUD_Redraw)(float time, int intermission);
_HUD_Frame ORIG_HUD_Frame = NULL;
_HUD_Redraw ORIG_HUD_Redraw = NULL;

typedef void (*_LoadThisDll)(char* szDllFilename);
_LoadThisDll ORIG_LoadThisDll = NULL;

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

CChaos gChaos;
CImGuiManager gImGui;

ma_engine miniAudio;

_wglSwapBuffers ORIG_wglSwapBuffers = NULL;
_WndProc ORIG_WndProc = NULL;

HWND g_hWndOfGame;

std::vector<const char*> g_szExportedWeaponList, g_szExportedEntityList;

bool g_bDrawHUD;
bool g_bHL25 = false;
bool g_bPreSteamPipe = false;

bool g_bEncrypted = false;

extern texture_t** r_notexture_mip;
extern volatile dma_t* shm;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
inline long __stdcall HOOKED_WndProc(const HWND a1, unsigned int a2, unsigned a3, long a4)
{
	ImGui_ImplWin32_WndProcHandler(a1, a2, a3, a4);
	return CallWindowProcA(ORIG_WndProc, a1, a2, a3, a4);
}

// OPENGL
_wglSwapBuffers GetSwapBuffersAddr()
{
	return reinterpret_cast<_wglSwapBuffers>(GetProcAddress(LoadLibrary(TEXT("OpenGL32.dll")), "wglSwapBuffers"));
}

int __stdcall HOOKED_wglSwapBuffers(HDC a1)
{
	static bool initialized = false;
	if (!initialized)
	{
		HookEngine();
		HookClient();
		MH_EnableHook(MH_ALL_HOOKS);

		g_hWndOfGame = WindowFromDC(a1);

		ORIG_WndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(g_hWndOfGame, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HOOKED_WndProc)));
		
		gImGui.Init();
		gImGui.InitBackends(g_hWndOfGame);
		gChaos.LoadFonts();

		initialized = true;
	}

	gImGui.Draw();

	return ORIG_wglSwapBuffers(a1);
}

// CLIENT
void HOOKED_HUD_Frame(double time)
{
	static bool initialized = false;
	if (!initialized)
	{
		gChaos.Init();
		initialized = true;
	}

	ORIG_HUD_Frame(time);
	gChaos.OnFrame(time);
}

int HOOKED_HUD_Redraw(float time, int intermission)
{
	return g_bDrawHUD ? 1 : ORIG_HUD_Redraw(time, intermission);
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
			if (strstr(functionName, "furniture") || strstr(functionName, "cine") || strstr(functionName, "repel") || strstr(functionName, "maw") || strstr(functionName, "generic") || strstr(functionName, "mortar"))
				continue;

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

void HookClient()
{
	g_lpClient = GetModuleHandle("client.dll");

	if (!g_lpClient)
		return;

	int status;

	Find(Client, HUD_Frame);
	Find(Client, HUD_Redraw);
	CreateHook(Client, HUD_Frame);
	CreateHook(Client, HUD_Redraw);
}

void HookEngine()
{
	static void* base;
	static size_t size;

	// now it's broken again so you can't restart the game via engine's _restart
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
			case 0: // HL-9920
				DEBUG_PRINT("Searching pEngfuncs in HL-9920 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 0x18B);

				if (pEngfuncs)
					DEBUG_PRINT("[hw dll] Found cl_enginefuncs at 0x%p.\n", pEngfuncs);

				break;
			case 1: // HL-8684
				DEBUG_PRINT("Searching pEngfuncs in HL-8684 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 181);

				if (pEngfuncs)
					DEBUG_PRINT("[hw dll] Found cl_enginefuncs at 0x%p.\n", pEngfuncs);

				break;
			case 2: // HL-4554
				DEBUG_PRINT("Searching pEngfuncs in HL-4554 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 226);

				if (pEngfuncs)
					DEBUG_PRINT("[hw dll] Found cl_enginefuncs at 0x%p.\n", pEngfuncs);

				break;
			case 3: // HL-3248
				DEBUG_PRINT("Searching pEngfuncs in HL-3248 pattern...\n");
				pEngfuncs = *reinterpret_cast<cl_enginefunc_t**>(reinterpret_cast<uintptr_t>(ClientDLL_Init) + 203);

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
			case 3:
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
			
			}
		});

	int status;

	SPTFind(LoadThisDll);
	EngineCreateHook(LoadThisDll);

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

	ma_result result = ma_engine_init(NULL, &miniAudio);
	if (result != MA_SUCCESS)
	{
		MessageBoxA(NULL, "Failed to initialize MiniAudio. Exiting...", "GSChaos", MB_OK | MB_ICONERROR);
		exit(1);
		return;
	}

	HookOpenGL();
}

extern "C" __declspec(dllexport) void ASIShutdown()
{
	gChaos.Shutdown();
	ma_engine_uninit(&miniAudio);
	MH_Uninitialize();
}

/*
================
DllMain
================
*/
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL); // said to increase performance?
		//CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(ASIMain), NULL, NULL, NULL); // start another thread running the hooking stuff
		return TRUE;
	}

	return FALSE;
}