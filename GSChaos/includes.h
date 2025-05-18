/**
 * Copyright - ScriptedSnark, 2024-2025.
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
#include <DbgHelp.h>

//STL
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <array>
#include <random>
#include <fstream>
#include <filesystem>
#include <queue>

//GL
#include <gl/glew.h>
#include <gl/GL.h>
#include "Shader.h"

//SOLOUD
#include "soloud.h"
#include "soloud_wav.h"
#include "ChaosLoudManager.h"

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
#include "in_camera.h"

extern CImGuiManager gImGui;

extern void* g_lpClient;
extern void* g_lpOpenGL32;
extern void* g_lpHW;

extern cl_enginefunc_t* pEngfuncs;
extern enginefuncs_t* g_engfuncs;
extern globalvars_t* gpGlobals;
extern DLL_FUNCTIONS* gEntityInterface;
extern server_t* sv;
extern client_state_t* cl;
extern client_state_HL25_t* cl_hl25;
extern ref_params_t* g_pRefParams;
extern engine_studio_api_t* engine_studio_api;

extern bool g_bEncrypted;

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
#include "CFeatureHighGravity.h"
#include "CFeatureZeroGravity.h"
#include "CFeatureInvisibleEntities.h"
#include "CFeatureOhio.h"
#include "CFeatureNothing.h"
#include "CFeatureDarkness.h"
#include "CFeatureTotem.h"
#include "CFeatureForgotCSS.h"
#include "CFeatureGodMode.h"
#include "CFeatureGlobalGodMode.h"
#include "CFeatureExplosion.h"
#include "CFeatureIchthyosaur.h"
#include "CFeatureGiveRandomWeapon.h"
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
#include "CFeatureGravityField.h"
#include "CFeatureIceSkating.h"
#include "CFeatureInvertVelocity.h"
#include "CFeatureNeedForSpeed.h"
#include "CFeatureMakeItBunDem.h"
#include "CFeatureBikiniBottom.h"
#include "CFeatureX10Gravity.h"
#include "CFeatureOverwriteQuicksave.h"
#include "CFeatureStop.h"
#include "CFeatureNoclip.h"
#include "CFeatureGiveHealth.h"
#include "CFeatureHL2Movement.h"
#include "CFeatureGiveArmor.h"
#include "CFeatureAmIDead.h"
#include "CFeatureNodeGraphRebuilding.h"
#include "CFeatureExtremeGrieferShephard.h"
#include "CFeatureInsaneStepsize.h"
#include "CFeatureDeleteRandomEntity.h"
#include "CFeatureNuke.h"
#include "CFeaturePlusDuck.h"
#include "CFeatureMonsterWorldspawn.h"
#include "CFeatureSpawnFastrun.h"
#include "CFeatureWorldHallucination.h"
#include "CFeatureGiveOneHP.h"
#include "CFeatureTakeOneHP.h"
#include "CFeatureScientistMadness.h"
#include "CFeatureMLGAudio.h"
#include "CFeatureNoHUD.h"
#include "CFeatureQuakePro.h"
#include "CFeatureNegativeAccelerate.h"
#include "CFeatureNice.h"
#include "CFeatureSqueakShephard.h"
#include "CFeatureSqueakShephards.h"
#include "CFeatureBoost.h"
#include "CFeatureNotarget.h"
#include "CFeatureHalfGravity.h"
#include "CFeatureRollin.h"
#include "CFeatureHigh.h"
#include "CFeatureShake.h"
#include "CFeatureSlap.h"
#include "CFeaturePlayAG.h"
#include "CFeatureSwapHealth.h"
#include "CFeatureTeleportToRandomNPC.h"
#include "CFeatureShuffleEntitiesPositions.h"
#include "CFeatureWideNPCs.h"
#include "CFeatureUltraWideNPCs.h"
#include "CFeatureTinyNPCs.h"
#include "CFeaturePaperNPCs.h"
#include "CFeatureGiveOneArmor.h"
#include "CFeatureReplaceModelsWithPlayer.h"
#include "CFeatureHorrorAudio.h"
#include "CFeatureLowFOV.h"
#include "CFeatureDisableChaosUI.h"
#include "CFeatureRandomFog.h"
#include "CFeatureWorstBhopCap.h"
#include "CFeatureLongJump.h"
#include "CFeatureReloadAutosave.h"
#include "CFeatureExtremeGrieferJesus.h"
#include "CFeatureMegaJump.h"
#include "CFeatureSpawn5RandomEntities.h"
#include "CFeatureGiveAllWeapons.h"
#include "CFeatureWaterIsALie.h"
#include "CFeatureQuakeJumpSound.h"
#include "CFeatureHook.h"
#include "CFeatureSpawnTeleport.h"
#include "CFeatureMirrorScreen.h"
#include "CFeatureWideScreen.h"
#include "CFeatureCreepypasta.h"
#include "CFeatureMessWorld.h"
#include "CFeatureKickWorld.h"
#include "CFeatureTallWorld.h"
#include "CFeatureTrapPlayer.h"
#include "CFeatureThirdPerson.h"
#include "CFeatureModelInsanity.h"
#include "CFeatureHalfGameSpeed.h"
#include "CFeatureStandstill.h"
#include "CFeatureGameSpeedup.h"
#include "CFeatureGambling.h"
#include "CFeatureRandomGameSpeed.h"
#include "CFeatureTurbulentHell.h"
#include "CFeatureNAAim.h"
#include "CFeatureTempEntityMadness.h"
#include "CFeatureEUAim.h"
#include "CFeatureScrollingHell.h"
#include "CFeatureDelete5RandomEntities.h"
#include "CFeatureKilometer.h"
#include "CFeatureDinnerbone.h"
#include "CFeatureMinerals.h"
#include "CFeatureMoveAllNPCsToPlayer.h"
#include "CFeatureChipmunks.h"
#include "CFeatureFloatingPointInaccuracy.h"
#include "CFeatureEBoost.h"
#include "CFeatureViewOfsInsanity.h"
#include "CFeatureOverwriteAutosave.h"
#include "CFeatureOverthinking.h"
#include "CFeatureNightvision.h"
#include "CFeatureVoidclip.h"
#include "CFeatureLowDrawDistance.h"
#include "CFeatureSuperhot.h"
#include "CFeatureNoAttacking.h"
#include "CFeaturePortrait.h"
#include "CFeatureDisableOneMovementKey.h"
#include "CFeatureInvertMovementInputs.h"
#include "CFeatureOHKO.h"
#include "CFeatureInputDelay.h"
#include "CFeatureBlur.h"
#include "CFeatureMaxwell.h"
#include "CFeatureSwapAttacks.h"
#include "CFeatureTwitchy.h"
#include "CFeaturePunchangle.h"
#include "CFeatureNoSaveLoading.h"
#include "CFeatureFirework.h"
#include "CFeatureEarthquake.h"
#include "CFeatureMovetypeBounce.h"
#include "CFeatureFiftyPercentDeath.h"
#include "CFeatureWhereAreYouGoing.h"
#include "CFeatureWaterPush.h"
#include "CFeatureGalangaAmbush.h"
#include "CFeatureArmorSpeedometer.h"

#include "CFeatureCheatCodeVoting.h"
#include "CFeatureCombineEffects.h"
#include "CFeature10Effects.h"
#include "CFeature10GoodEffects.h"
#include "CFeatureComboTime.h"
//========================

#include "CChaos.h"
#include "ChaosStats.h"
#include "CrashHandler.h"

extern HWND g_hWndOfGame;
extern Utils utils;
extern CChaos gChaos;
extern SoLoud::Soloud gSoloud; // SoLoud engine

extern bool g_bActivatedGTA3HUD;

#define GS_DEBUG

#define CHAOS_PATH "../chaos/"

#ifdef GS_DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...) ((void)0)
#endif

#define Find(lib, func_name) \
    if ((ORIG_##func_name = reinterpret_cast<_##func_name>(GetProcAddress(reinterpret_cast<HMODULE>(g_lp##lib), #func_name)))) \
        printf("[client dll] Found " #func_name " at %p.\n", ORIG_##func_name); \
    else \
        printf("[client dll] Could not find " #func_name ".\n");


#define EngineCreateHook(func_name) \
		if (g_bEncrypted) { MemUtils::MarkAsExecutable(ORIG_##func_name); }\
        status = MH_CreateHook(ORIG_##func_name, HOOKED_##func_name, reinterpret_cast<void**>(&ORIG_##func_name)); \
        if (status != MH_OK) { \
            printf("[hw dll] Couldn't create hook for " #func_name ".\n"); \
        }

#define CreateHook(lib, func_name) \
        status = MH_CreateHook(ORIG_##func_name, HOOKED_##func_name, reinterpret_cast<void**>(&ORIG_##func_name)); \
        if (status != MH_OK) { \
            printf("[" #lib "] Couldn't create hook for " #func_name ".\n"); \
        }

#define SPTFind(future_name)                                                                                                                  \
	{                                                                                                                                      \
		auto f##future_name = utils.FindAsync(ORIG_##future_name, patterns::engine::future_name);                                          \
		auto pattern = f##future_name.get();                                                                                               \
		if (ORIG_##future_name)                                                                                                            \
		{                                                                                                                                  \
			printf("[hw dll] Found " #future_name " at %p (using the %s pattern).\n", ORIG_##future_name, pattern->name()); \
		}                                                                                                                                  \
	}

#pragma comment(lib, "opengl32.lib")

#else //!__cplusplus
#error C++ compiler required to compile includes.h
#endif //__cplusplus

#endif //INCLUDES_H_GUARD

#undef INCLUDES_H_RECURSE_GUARD
#endif //INCLUDES_H_RECURSE_GUARD