/**
 * Copyright - ScriptedSnark, 2024.
 * includes.h - includes of project
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef INCLUDES_H_RECURSE_GUARD
#error Recursive header files inclusion detected in includes.h
#else //INCLUDES_H_RECURSE_GUARD

#define INCLUDES_H_RECURSE_GUARD

#ifndef INCLUDES_H_GUARD
#define INCLUDES_H_GUARD
#pragma once

#ifdef __cplusplus

//WINDOWS
#include <windows.h>

//STL
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <array>
#include <random>
#include <fstream>

//GL
#include <gl/GL.h>

//MINIAUDIO
#include "miniaudio.h"
extern ma_engine miniAudio;

//IMGUI
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_win32.h"
#include "imgui_manager.hpp"
#include "pricedown.h"
#include "arial_black.h"
#include "sf_arborcrest.h"
#include "arial_black_italic.h"

//HOOK
#include "MinHook.h"
#include "MemUtils.h"
#include "patterns.hpp"
#include "Utils.hpp"
#include "engine_patterns.hpp"

#include "functional_lite_rng.hpp"

//SDK
#include "hlsdk_mini.hpp"
#include "engine/sound.h"
#include "engine/svc_messages.h"
#include "engine/model.h"
#include "parsemsg.h"
#include "Utils.h"
#include "dynamic_precache.h"
#include "CLWrapper.h"

extern cl_enginefunc_t* pEngfuncs;
extern enginefuncs_t* g_engfuncs;
extern globalvars_t* gpGlobals;
extern DLL_FUNCTIONS* gEntityInterface;
extern server_t* sv;
extern client_state_t* cl;
extern client_state_HL25_t* cl_hl25;

#define STRING(offset)		((const char *)(gpGlobals->pStringBase + (unsigned int)(offset)))
#define MAKE_STRING(str)	((uint64)(str) - (uint64)(STRING(0)))

#define MAX_WEAPONS 64

#include "engine/enginecallback.h"

//GSChaos
#include "GSChaos.h"
#include "CChaosFeature.h"

//Features (Effects)
//========================
#include "CFeatureNewGame.h"
#include "CFeatureSet1HP.h"
#include "CFeatureAudioCorrupt.h"
#include "CFeatureFly.h"
#include "CFeatureRemoveArmor.h"
#include "CFeatureZeroGravity.h"
#include "CFeatureInvisibleEntities.h"
#include "CFeatureOhio.h"
#include "CFeatureFakeCrash.h"
#include "CFeatureDarkness.h"
#include "CFeatureTotem.h"
#include "CFeatureForgotCSS.h"
#include "CFeatureHighGravity.h"
#include "CFeatureGodMode.h"
#include "CFeatureGlobalGodMode.h"
#include "CFeatureExplosion.h"
#include "CFeatureIchthyosaur.h"
#include "CFeatureGiveGauss.h"
#include "CFeatureGruntAmbush.h"
#include "CFeatureGTA3HUD.h"
#include "CFeatureWeaponStrip.h"
#include "CFeatureGrieferShephard.h"
#include "CFeatureEntitySpin.h"
#include "CFeatureGTA2Camera.h"
#include "CFeatureOnePercentDeath.h"
#include "CFeatureSpawnRandomEntity.h"
#include "CFeatureSleepy.h"
#include "CFeature20FPS.h"
#include "CFeatureBSPDementia.h"
#include "CFeatureHEVMadness.h"
#include "CFeatureNegativeStepsize.h"
#include "CFeatureLobotomy.h"
#include "CFeatureUpsideDown.h"
#include "CFeatureNPCExplode.h"
#include "CFeatureJeepy.h"

#include "CFeatureCombineEffects.h"
//========================

#include "CChaos.h"

extern HWND g_hWndOfGame;
extern Utils utils;
extern CChaos gChaos;

extern bool g_bActivatedGTA3HUD;

//#define GS_DEBUG

#ifdef GS_DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

#define Find(lib, func_name) \
    if ((ORIG_##func_name = reinterpret_cast<_##func_name>(GetProcAddress(reinterpret_cast<HMODULE>(g_lp##lib), #func_name)))) \
        DEBUG_PRINT("[client dll] Found " #func_name " at %p.\n", ORIG_##func_name); \
    else \
        DEBUG_PRINT("[client dll] Could not find " #func_name ".\n");


#define CreateHook(func_name) \
        status = MH_CreateHook(ORIG_##func_name, HOOKED_##func_name, reinterpret_cast<void**>(&ORIG_##func_name)); \
        if (status != MH_OK) { \
            DEBUG_PRINT("[client dll] Couldn't create hook for " #func_name ".\n"); \
        }

#define SPTFind(future_name)                                                                                                                  \
	{                                                                                                                                      \
		auto f##future_name = utils.FindAsync(ORIG_##future_name, patterns::engine::future_name);                                          \
		auto pattern = f##future_name.get();                                                                                               \
		if (ORIG_##future_name)                                                                                                            \
		{                                                                                                                                  \
			DEBUG_PRINT("[hw dll] Found " #future_name " at %p (using the %s pattern).\n", ORIG_##future_name, pattern->name()); \
		}                                                                                                                                  \
	}

#pragma comment(lib, "opengl32.lib")

#else //!__cplusplus
#error C++ compiler required to compile includes.h
#endif //__cplusplus

#endif //INCLUDES_H_GUARD

#undef INCLUDES_H_RECURSE_GUARD
#endif //INCLUDES_H_RECURSE_GUARD