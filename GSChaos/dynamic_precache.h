/**
 * Copyright - ScriptedSnark, 2024.
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

void InitDynamicPrecache();
int GetModelByIndex(const char* name);

#else //!__cplusplus
#error C++ compiler required to compile dynamic_precache.h
#endif //__cplusplus

#endif //DYNAMIC_PRECACHE_H_GUARD

#undef DYNAMIC_PRECACHE_H_RECURSE_GUARD
#endif //DYNAMIC_PRECACHE_H_RECURSE_GUARD