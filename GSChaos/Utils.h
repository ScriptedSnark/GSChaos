/**
 * Copyright - ScriptedSnark, 2024.
 * Utils.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef UTILS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in Utils.h
#else //UTILS_H_RECURSE_GUARD

#define UTILS_H_RECURSE_GUARD

#ifndef UTILS_H_GUARD
#define UTILS_H_GUARD
#pragma once

#ifdef __cplusplus

void Draw_FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a);
char* UTIL_VarArgs(char* format, ...);
edict_t* UTIL_FindEntityInSphere(edict_t* pStartEntity, const Vector& vecCenter, float flRadius);
typedef enum { ignore_monsters = 1, dont_ignore_monsters = 0, missile = 2 } IGNORE_MONSTERS;
typedef enum { ignore_glass = 1, dont_ignore_glass = 0 } IGNORE_GLASS;
void UTIL_MakeAimVectors(const Vector& vecAngles);
Vector UTIL_VecToAngles(const Vector& vec);
extern void			UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, IGNORE_MONSTERS igmon, edict_t* pentIgnore, TraceResult* ptr);
extern void			UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t* pentIgnore, TraceResult* ptr);
bool LoadTextureFromFile(const char* filename, GLuint* out_texture);

#else //!__cplusplus
#error C++ compiler required to compile Utils.h
#endif //__cplusplus

#endif //UTILS_H_GUARD

#undef UTILS_H_RECURSE_GUARD
#endif //UTILS_H_RECURSE_GUARD