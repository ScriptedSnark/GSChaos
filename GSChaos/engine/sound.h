/***
 *
 *	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
 *
 *	This product contains software technology licensed from Id
 *	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
 *	All Rights Reserved.
 *
 *   Use, distribution, and modification of this source code and/or resulting
 *   object code is restricted to non-commercial enhancements to products from
 *   Valve LLC.  All other use, distribution, or modification is prohibited
 *   without written permission from Valve LLC.
 *
 ****/

 // sound.h -- client sound i/o functions

#ifndef SOUND_H
#define SOUND_H
#ifdef _WIN32
#pragma once
#endif

#define MAX_QPATH 64    // Must match value in quakedefs.h

#define PAINTBUFFER_SIZE 512

// sound engine rate defines
#define SOUND_DMA_SPEED 22050 // hardware playback rate

#define SOUND_11k 11025 // 11khz sample rate

// sentence groups
#define CBSENTENCENAME_MAX 16
#define CVOXFILESENTENCEMAX 1536 // max number of sentences in game. NOTE: this must match
								 // CVOXFILESENTENCEMAX in dlls\util.h!!!

//=====================================================================
// FX presets
//=====================================================================

#define SXROOM_OFF 0

#define SXROOM_GENERIC 1 // general, low reflective, diffuse room

#define SXROOM_METALIC_S 2 // highly reflective, parallel surfaces
#define SXROOM_METALIC_M 3
#define SXROOM_METALIC_L 4

#define SXROOM_TUNNEL_S 5 // resonant reflective, long surfaces
#define SXROOM_TUNNEL_M 6
#define SXROOM_TUNNEL_L 7

#define SXROOM_CHAMBER_S 8 // diffuse, moderately reflective surfaces
#define SXROOM_CHAMBER_M 9
#define SXROOM_CHAMBER_L 10

#define SXROOM_BRITE_S 11 // diffuse, highly reflective
#define SXROOM_BRITE_M 12
#define SXROOM_BRITE_L 13

#define SXROOM_WATER1 14 // underwater fx
#define SXROOM_WATER2 15
#define SXROOM_WATER3 16

#define SXROOM_CONCRETE_S 17 // bare, reflective, parallel surfaces
#define SXROOM_CONCRETE_M 18
#define SXROOM_CONCRETE_L 19

#define SXROOM_OUTSIDE1 20 // echoing, moderately reflective
#define SXROOM_OUTSIDE2 21 // echoing, dull
#define SXROOM_OUTSIDE3 22 // echoing, very dull

#define SXROOM_CAVERN_S 23 // large, echoing area
#define SXROOM_CAVERN_M 24
#define SXROOM_CAVERN_L 25

#define SXROOM_WEIRDO1 26
#define SXROOM_WEIRDO2 27
#define SXROOM_WEIRDO3 28

#define CSXROOM 29

// !!! if this is changed, it much be changed in asm_i386.h too !!!
struct portable_samplepair_t
{
	int left;
	int right;
};

struct sfx_t
{
	char name[MAX_QPATH];
	cache_user_t cache;
	int servercount;
};

// !!! if this is changed, it much be changed in asm_i386.h too !!!
struct sfxcache_t
{
	int length;
	int loopstart;
	int speed;
	int width;
	int stereo;
	byte data[1]; // variable sized
};

struct dma_t
{
	qboolean gamealive;
	qboolean soundalive;
	qboolean splitbuffer;
	int channels;
	int samples;		  // mono samples in buffer
	int submission_chunk; // don't mix less than this #
	int samplepos;		  // in mono samples
	int samplebits;
	int speed;
	int dmaspeed;
	unsigned char* buffer;
};

// !!! if this is changed, it much be changed in asm_i386.h too !!!
struct channel_t
{
	sfx_t* sfx;	  // sfx number
	int leftvol;  // 0-255 volume
	int rightvol; // 0-255 volume

	int end; // end time in global paintsamples
	int pos; // sample position in sfx

	int looping; // where to loop, -1 = no looping

	int entnum;		// to allow overriding a specific sound
	int entchannel; // TODO: Define as enum, modify const.h then -Enko

	vec3_t origin;	 // origin of sound effect
	vec_t dist_mult; // distance multiplier (attenuation/clipK)

	int master_vol; // 0-255 master volume

	int isentence; // true if playing linked sentence
	int iword;

	int pitch;
};

struct wavinfo_t
{
	int rate;
	int width;
	int channels;
	int loopstart;
	int samples;
	int dataofs; // chunk starts this many bytes from file start
};

struct wavstream_t
{
	int csamplesplayed;
	int csamplesinmem;
	void* hFile;
	wavinfo_t info;
	int lastposloaded;
};

struct voxword_t
{
	int volume;		  // increase percent, ie: 125 = 125% increase
	int pitch;		  // pitch shift up percent
	int start;		  // offset start of wave percent
	int end;		  // offset end of wave percent
	int cbtrim;		  // end of wave after being trimmed to 'end'
	int fKeepCached;  // 1 if this word was already in cache before sentence referenced it
	int samplefrac;	  // if pitch shifting, this is position into wav * 256
	int timecompress; // % of wave to skip during playback (causes no pitch shift)
	sfx_t* sfx;		  // name and cache pointer
};

#define CVOXWORDMAX 32

// ====================================================================
// User-setable variables
// ====================================================================

#define MAX_CHANNELS 128
#define MAX_DYNAMIC_CHANNELS 8

#endif // SOUND_H