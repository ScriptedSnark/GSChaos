/**
 * Copyright - ScriptedSnark, 2024-2025.
 * dynamic_precache.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef DYNAMIC_PRECACHE_H_RECURSE_GUARD
#error Recursive header files inclusion detected in dynamic_precache.h
#else //DYNAMIC_PRECACHE_H_RECURSE_GUARD

#define DYNAMIC_PRECACHE_H_RECURSE_GUARD

#ifndef DYNAMIC_PRECACHE_H_GUARD
#define DYNAMIC_PRECACHE_H_GUARD
#pragma once

#ifdef __cplusplus

extern int g_ErrorModel;

typedef sfxcache_t* (*_S_LoadSound)(sfx_t* s, channel_t* ch);
typedef sfx_t* (*_S_FindName)(char* name, int* pfInCache);
typedef model_t* (*_Mod_ForName)(const char* name, qboolean crash, qboolean trackCRC);
typedef int (*_PF_precache_model_I)(char* s);
typedef int (*_PF_precache_sound_I)(char* s);
typedef unsigned short (*_EV_Precache)(int type, const char* psz);
typedef void (*_PF_setmodel_I)(edict_t* e, const char* m);
typedef void (*_SV_AddSampleToHashedLookupTable)(const char* pszSample, int iSampleIndex);

extern _S_LoadSound ORIG_S_LoadSound;
extern _S_FindName ORIG_S_FindName;
extern _Mod_ForName ORIG_Mod_ForName;
extern _PF_precache_model_I ORIG_PF_precache_model_I;
extern _PF_precache_sound_I ORIG_PF_precache_sound_I;
extern _PF_setmodel_I ORIG_PF_setmodel_I;
extern _EV_Precache ORIG_EV_Precache;
extern _SV_AddSampleToHashedLookupTable ORIG_SV_AddSampleToHashedLookupTable;

void InitDynamicPrecache();
sfx_t* S_LateLoadSound(char* name);
int GetModelByIndex(const char* name);

#else //!__cplusplus
#error C++ compiler required to compile dynamic_precache.h
#endif //__cplusplus

#endif //DYNAMIC_PRECACHE_H_GUARD

#undef DYNAMIC_PRECACHE_H_RECURSE_GUARD
#endif //DYNAMIC_PRECACHE_H_RECURSE_GUARD