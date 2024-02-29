#ifdef MODEL_H_RECURSE_GUARD
#error Recursive header files inclusion detected in model.h
#else //MODEL_H_RECURSE_GUARD

#define MODEL_H_RECURSE_GUARD

#ifndef MODEL_H_GUARD
#define MODEL_H_GUARD
#pragma once

#ifdef __cplusplus

#define ALIAS_MODEL_VERSION	0x006

#define MAX_LBM_HEIGHT		480
#define MAX_ALIAS_MODEL_VERTS	2000

#define SURF_PLANEBACK		2
#define SURF_DRAWSKY		4
#define SURF_DRAWSPRITE		8
#define SURF_DRAWTURB		0x10
#define SURF_DRAWTILED		0x20
#define SURF_DRAWBACKGROUND	0x40

#define MAX_MODEL_NAME		64
#define MIPLEVELS			4
#define NUM_AMBIENTS		4		// automatic ambient sounds
#define MAXLIGHTMAPS		4
#define MAX_KNOWN_MODELS	1024

typedef struct texture_s
{
	char			name[16];
	unsigned		width, height;

#if !defined(SWDS) && !defined(HLTV)
	int			gl_texturenum;
	struct msurface_s* texturechain;
#endif

	int				anim_total;			// total tenths in sequence ( 0 = no)
	int				anim_min, anim_max;	// time for this frame min <=time< max
	struct texture_s* anim_next;		// in the animation sequence
	struct texture_s* alternate_anims;	// bmodels in frame 1 use these
	unsigned		offsets[MIPLEVELS];	// four mip maps stored

#if defined(SWDS) || defined(HLTV)
	unsigned		paloffset;
#else
	byte* pPal;
#endif

} texture_t;

#else //!__cplusplus
#error C++ compiler required to compile model.h
#endif //__cplusplus

#endif //MODEL_H_GUARD

#undef MODEL_H_RECURSE_GUARD
#endif //MODEL_H_RECURSE_GUARD