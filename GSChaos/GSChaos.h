/**
 * Copyright - ScriptedSnark, 2024.
 * GSChaos.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef GSCHAOS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in GSChaos.h
#else //GSCHAOS_H_RECURSE_GUARD

#define GSCHAOS_H_RECURSE_GUARD

#ifndef GSCHAOS_H_GUARD
#define GSCHAOS_H_GUARD
#pragma once

#ifdef __cplusplus

struct TwitchVoter
{
	std::string userName;
	int value;
};

typedef int(__stdcall* _wglSwapBuffers)(HDC);
typedef LRESULT (APIENTRY* _WndProc)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern _wglSwapBuffers ORIG_wglSwapBuffers;
extern _WndProc ORIG_WndProc;

extern std::vector<const char*> g_szExportedWeaponList;
extern std::vector<const char*> g_szExportedEntityList;

extern bool g_bHL25;
extern bool g_bPreSteamPipe;
extern bool g_bDrawHUD;

extern qboolean g_FogSkybox, g_FogOn;
extern float g_FogDensity, g_FogStartDistance, g_FogStopDistance;
extern float g_FogColor[4], g_FogColorRGB[4];

void InitFog();
void RenderFog();
void DisableFog();

bool IsEntityAvailable(const char* entityName);

void HookEngine();
void HookClient();

#else //!__cplusplus
#error C++ compiler required to compile GSChaos.h
#endif //__cplusplus

#endif //GSCHAOS_H_GUARD

#undef GSCHAOS_H_RECURSE_GUARD
#endif //GSCHAOS_H_RECURSE_GUARD