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

#define FFADE_IN			0x0000		// Just here so we don't pass 0 into the function
#define FFADE_OUT			0x0001		// Fade out (not in)
#define FFADE_MODULATE		0x0002		// Modulate (don't blend)
#define FFADE_STAYOUT		0x0004		// ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_LONGFADE		0x0008		// used to indicate the fade can be longer than 16 seconds (added for czero)

#define TEXTURE_BASEID 12000
extern int g_iTextureCounter;
 // This structure is sent over the net to describe a screen fade event
typedef struct
{
	unsigned short 	duration;		// FIXED 4.12 seconds duration
	unsigned short 	holdTime;		// FIXED 4.12 seconds duration until reset (fade & hold)
	short			fadeFlags;		// flags
	byte			r, g, b, a;		// fade to color ( max alpha )
} ScreenFade;

// This structure is sent over the net to describe a screen shake event
typedef struct
{
	unsigned short	amplitude;		// FIXED 4.12 amount of shake
	unsigned short 	duration;		// FIXED 4.12 seconds duration
	unsigned short	frequency;		// FIXED 8.8 noise frequency (low frequency is a jerk,high frequency is a rumble)
} ScreenShake;

typedef struct hudtextparms_s
{
	float		x;
	float		y;
	int			effect;
	byte		r1, g1, b1, a1;
	byte		r2, g2, b2, a2;
	float		fadeinTime;
	float		fadeoutTime;
	float		holdTime;
	float		fxTime;
	int			channel;
} hudtextparms_t;


void _AngleVectors(const Vector angles, Vector forward, Vector right, Vector up);
float Length(const vec3_t v);
void Draw_FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a);
char* UTIL_VarArgs(char* format, ...);
edict_t* UTIL_FindEntityInSphere(edict_t* pStartEntity, const Vector& vecCenter, float flRadius);
typedef enum { ignore_monsters = 1, dont_ignore_monsters = 0, missile = 2 } IGNORE_MONSTERS;
typedef enum { ignore_glass = 1, dont_ignore_glass = 0 } IGNORE_GLASS;
void UTIL_MakeAimVectors(const Vector& vecAngles);
Vector UTIL_VecToAngles(const Vector& vec);
void UTIL_MakeVectors(const Vector& vecAngles);
extern void			UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, IGNORE_MONSTERS igmon, edict_t* pentIgnore, TraceResult* ptr);
extern void			UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t* pentIgnore, TraceResult* ptr);
void UTIL_ScreenShake(const Vector& center, float amplitude, float frequency, float duration, float radius);
void UTIL_ScreenFade(edict_t* pEntity, const Vector& color, float fadeTime, float fadeHold, int alpha, int flags);
void UTIL_TakeDamage(entvars_t& pevInflictor, float flDamage, int bitsDamageType);
void UTIL_HudMessage(edict_t* pEntity, const hudtextparms_t& textparms, const char* pMessage);
bool LoadTextureFromFile(const char* filename, GLuint* out_texture);
bool LoadTexturesFromFiles(const char* base_filename, byte frames, unsigned char** image_frames, int* image_width, int* image_height);
float UTIL_Hue2RGB(float p, float q, float t);
Vector UTIL_HSL2RGB(Vector _HSL);
float UTIL_GetScreenCoord(float flValue);

#else //!__cplusplus
#error C++ compiler required to compile Utils.h
#endif //__cplusplus

#endif //UTILS_H_GUARD

#undef UTILS_H_RECURSE_GUARD
#endif //UTILS_H_RECURSE_GUARD