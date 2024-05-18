#pragma once

#ifndef M_PI
const double M_PI = 3.14159265358979323846;
#endif

/* CVAR FLAGS - START */
#define FCVAR_ARCHIVE        (1<<0)    // set to cause it to be saved to vars.rc
#define FCVAR_USERINFO        (1<<1)    // changes the client's info string
#define FCVAR_SERVER        (1<<2)    // notifies players when changed
#define	FCVAR_EXTDLL        (1<<3)    // defined by external DLL
#define FCVAR_CLIENTDLL     (1<<4)  // defined by the client dll
#define FCVAR_PROTECTED     (1<<5)  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
#define FCVAR_SPONLY        (1<<6)  // This cvar cannot be changed by clients connected to a multiplayer server.
#define FCVAR_PRINTABLEONLY (1<<7)  // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
#define FCVAR_UNLOGGED        (1<<8)  // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
#define FCVAR_NOEXTRAWHITEPACE    (1<<9)  // strip trailing/leading white space from this cvar
/* CVAR FLAGS - END */
#define vec3_t Vector
typedef float vec_t;				// needed before including progdefs.h
//=========================================================
// 2DVector - used for many pathfinding and many other 
// operations that are treated as planar rather than 3d.
//=========================================================
class Vector2D
{
public:
	inline Vector2D(void) { }
	inline Vector2D(float X, float Y) { x = X; y = Y; }
	inline Vector2D operator+(const Vector2D& v)	const { return Vector2D(x + v.x, y + v.y); }
	inline Vector2D operator-(const Vector2D& v)	const { return Vector2D(x - v.x, y - v.y); }
	inline Vector2D operator*(float fl)				const { return Vector2D(x * fl, y * fl); }
	inline Vector2D operator/(float fl)				const { return Vector2D(x / fl, y / fl); }

	inline float Length(void)						const { return sqrt(x * x + y * y); }

	inline Vector2D Normalize(void) const
	{
		Vector2D vec2;

		float flLen = Length();
		if (flLen == 0)
		{
			return Vector2D(0, 0);
		}
		else
		{
			flLen = 1 / flLen;
			return Vector2D(x * flLen, y * flLen);
		}
	}

	vec_t	x = 0, y = 0;
};

inline float DotProduct(const Vector2D& a, const Vector2D& b) { return(a.x * b.x + a.y * b.y); }
inline Vector2D operator*(float fl, const Vector2D& v) { return v * fl; }
//=========================================================
// 3D Vector
//=========================================================
class Vector						// same data-layout as engine's vec3_t,
{								//		which is a vec_t[3]
public:
	// Construction/destruction
	inline Vector(void) { }
	inline Vector(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	//inline Vector(double X, double Y, double Z)		{ x = (float)X; y = (float)Y; z = (float)Z;	}
	//inline Vector(int X, int Y, int Z)				{ x = (float)X; y = (float)Y; z = (float)Z;	}
	inline Vector(const Vector& v) { x = v.x; y = v.y; z = v.z; }
	inline Vector(const float rgfl[3]) { x = rgfl[0]; y = rgfl[1]; z = rgfl[2]; }
	inline Vector& operator=(const Vector& v) { x = v.x; y = v.y; z = v.z; return *this; }

	// Operators
	inline Vector operator-(void) const { return Vector(-x, -y, -z); }
	inline int operator==(const Vector& v) const { return x == v.x && y == v.y && z == v.z; }
	inline int operator!=(const Vector& v) const { return !(*this == v); }
	inline Vector operator+(const Vector& v) const { return Vector(x + v.x, y + v.y, z + v.z); }
	inline Vector operator-(const Vector& v) const { return Vector(x - v.x, y - v.y, z - v.z); }
	inline Vector operator*(float fl) const { return Vector(x * fl, y * fl, z * fl); }
	inline Vector operator/(float fl) const { return Vector(x / fl, y / fl, z / fl); }
	inline Vector& operator+=(const Vector& v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline Vector& operator*=(float fl) { x *= fl; y *= fl; z *= fl; return *this; }

	// Methods
	inline void CopyToArray(float* rgfl) const { rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; }
	inline float Length(void) const { return sqrt(x * x + y * y + z * z); }
	operator float* () { return &x; } // Vectors will now automatically convert to float * when needed
	operator const float* () const { return &x; } // Vectors will now automatically convert to float * when needed
	inline Vector Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector(x * flLen, y * flLen, z * flLen);
	}

	inline Vector2D Make2D(void) const
	{
		Vector2D	Vec2;

		Vec2.x = x;
		Vec2.y = y;

		return Vec2;
	}
	inline float Length2D(void) const { return sqrt(x * x + y * y); }

	// Members
	vec_t x = 0, y = 0, z = 0;
};
inline Vector operator*(float fl, const Vector& v) { return v * fl; }
inline float DotProduct(const Vector& a, const Vector& b) { return(a.x * b.x + a.y * b.y + a.z * b.z); }
inline Vector CrossProduct(const Vector& a, const Vector& b) { return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

// edict->flags
#define FL_FLY           (1 << 0) // Changes the SV_Movestep() behavior to not need to be on ground
#define FL_SWIM          (1 << 1) // Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
#define FL_CONVEYOR      (1 << 2)
#define FL_CLIENT        (1 << 3)
#define FL_INWATER       (1 << 4)
#define FL_MONSTER       (1 << 5)
#define FL_GODMODE       (1 << 6)
#define FL_NOTARGET      (1 << 7)
#define FL_SKIPLOCALHOST (1 << 8) // Don't send entity to local host, it's predicting this entity itself
#define FL_ONGROUND      (1 << 9) // At rest / on the ground
#define FL_PARTIALGROUND (1 << 10) // not all corners are valid
#define FL_WATERJUMP     (1 << 11) // player jumping out of water
#define FL_FROZEN        (1 << 12) // Player is frozen for 3rd person camera
#define FL_FAKECLIENT    (1 << 13) // JAC: fake client, simulated server side; don't send network messages to them
#define FL_DUCKING       (1 << 14) // Player flag -- Player is fully crouched
#define FL_FLOAT         (1 << 15) // Apply floating force to this entity when in water
#define FL_GRAPHED       (1 << 16) // worldgraph has this ent listed as something that blocks a connection

// UNDONE: Do we need these?
#define FL_IMMUNE_WATER (1 << 17)
#define FL_IMMUNE_SLIME (1 << 18)
#define FL_IMMUNE_LAVA  (1 << 19)

#define FL_PROXY        (1 << 20) // This is a spectator proxy
#define FL_ALWAYSTHINK  (1 << 21) // Brush model flag -- call think every frame regardless of nextthink - ltime (for constantly changing velocity/path)
#define FL_BASEVELOCITY (1 << 22) // Base velocity has been applied this frame (used to convert base velocity into momentum)
#define FL_MONSTERCLIP  (1 << 23) // Only collide in with monsters who have FL_MONSTERCLIP set
#define FL_ONTRAIN      (1 << 24) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_WORLDBRUSH   (1 << 25) // Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
#define FL_SPECTATOR    (1 << 26) // This client is a spectator, don't run touch functions, etc.
#define FL_CUSTOMENTITY (1 << 29) // This is a custom entity
#define FL_KILLME       (1 << 30) // This entity is marked for death -- This allows the engine to kill ents at the appropriate time
#define FL_DORMANT      (1 << 31) // Entity is dormant, no updates to client

// Goes into globalvars_t.trace_flags
#define FTRACE_SIMPLEBOX (1 << 0) // Traceline with a simple box

// walkmove modes
#define WALKMOVE_NORMAL    0 // normal walkmove
#define WALKMOVE_WORLDONLY 1 // doesn't hit ANY entities, no matter what the solid type
#define WALKMOVE_CHECKONLY 2 // move, but don't touch triggers

// edict->movetype values
#define MOVETYPE_NONE 0 // never moves
//#define	MOVETYPE_ANGLENOCLIP	1
//#define	MOVETYPE_ANGLECLIP		2
#define MOVETYPE_WALK          3 // Player only - moving on the ground
#define MOVETYPE_STEP          4 // gravity, special edge handling -- monsters use this
#define MOVETYPE_FLY           5 // No gravity, but still collides with stuff
#define MOVETYPE_TOSS          6 // gravity/collisions
#define MOVETYPE_PUSH          7 // no clip to world, push and crush
#define MOVETYPE_NOCLIP        8 // No gravity, no collisions, still do velocity/avelocity
#define MOVETYPE_FLYMISSILE    9 // extra size to monsters
#define MOVETYPE_BOUNCE        10 // Just like Toss, but reflect velocity when contacting surfaces
#define MOVETYPE_BOUNCEMISSILE 11 // bounce w/o gravity
#define MOVETYPE_FOLLOW        12 // track movement of aiment
#define MOVETYPE_PUSHSTEP      13 // BSP model that needs physics/world collisions (uses nearest hull for world collision)

// edict->solid values
// NOTE: Some movetypes will cause collisions independent of SOLID_NOT/SOLID_TRIGGER when the entity moves
// SOLID only effects OTHER entities colliding with this one when they move - UGH!
#define SOLID_NOT      0 // no interaction with other objects
#define SOLID_TRIGGER  1 // touch on edge, but not blocking
#define SOLID_BBOX     2 // touch on edge, block
#define SOLID_SLIDEBOX 3 // touch on edge, but not an onground
#define SOLID_BSP      4 // bsp clip, touch on edge, block

// edict->deadflag values
#define DEAD_NO          0 // alive
#define DEAD_DYING       1 // playing death animation or still falling off of a ledge waiting to hit ground
#define DEAD_DEAD        2 // dead. lying still.
#define DEAD_RESPAWNABLE 3
#define DEAD_DISCARDBODY 4

#define DAMAGE_NO  0
#define DAMAGE_YES 1
#define DAMAGE_AIM 2

#define DMG_GENERIC			0			// generic damage was done
#define DMG_CRUSH			(1 << 0)	// crushed by falling or moving object
#define DMG_BULLET			(1 << 1)	// shot
#define DMG_SLASH			(1 << 2)	// cut, clawed, stabbed
#define DMG_BURN			(1 << 3)	// heat burned
#define DMG_FREEZE			(1 << 4)	// frozen
#define DMG_FALL			(1 << 5)	// fell too far
#define DMG_BLAST			(1 << 6)	// explosive blast damage
#define DMG_CLUB			(1 << 7)	// crowbar, punch, headbutt
#define DMG_SHOCK			(1 << 8)	// electric shock
#define DMG_SONIC			(1 << 9)	// sound pulse shockwave
#define DMG_ENERGYBEAM		(1 << 10)	// laser or other high energy beam 
#define DMG_NEVERGIB		(1 << 12)	// with this bit OR'd in, no damage type will be able to gib victims upon death
#define DMG_ALWAYSGIB		(1 << 13)	// with this bit OR'd in, any damage type can be made to gib victims upon death.
#define DMG_DROWN			(1 << 14)	// Drowning
// time-based damage
#define DMG_TIMEBASED		(~(0x3fff))	// mask for time-based damage

#define DMG_PARALYZE		(1 << 15)	// slows affected creature down
#define DMG_NERVEGAS		(1 << 16)	// nerve toxins, very bad
#define DMG_POISON			(1 << 17)	// blood poisioning
#define DMG_RADIATION		(1 << 18)	// radiation exposure
#define DMG_DROWNRECOVER	(1 << 19)	// drowning recovery
#define DMG_ACID			(1 << 20)	// toxic chemicals or acid burns
#define DMG_SLOWBURN		(1 << 21)	// in an oven
#define DMG_SLOWFREEZE		(1 << 22)	// in a subzero freezer
#define DMG_MORTAR			(1 << 23)	// Hit by air raid (done to distinguish grenade from mortar)

// these are the damage types that are allowed to gib corpses
#define DMG_GIB_CORPSE		( DMG_CRUSH | DMG_FALL | DMG_BLAST | DMG_SONIC | DMG_CLUB )

// these are the damage types that have client hud art
#define DMG_SHOWNHUD		(DMG_POISON | DMG_ACID | DMG_FREEZE | DMG_SLOWFREEZE | DMG_DROWN | DMG_BURN | DMG_SLOWBURN | DMG_NERVEGAS | DMG_RADIATION | DMG_SHOCK)

#define TYPE_CLIENT				0	// client is a normal HL client (default)
#define TYPE_PROXY				1	// client is another proxy
#define TYPE_COMMENTATOR		3	// client is a commentator
#define TYPE_DEMO				4	// client is a demo file

// sub commands of svc_hltv:
#define HLTV_ACTIVE				0	// tells client that he's an spectator and will get director commands
#define HLTV_STATUS				1	// send status infos about proxy 
#define HLTV_LISTEN				2	// tell client to listen to a multicast stream

// director command types:
#define DRC_CMD_NONE				0	// NULL director command
#define DRC_CMD_START				1	// start director mode
#define DRC_CMD_EVENT				2	// informs about director command
#define DRC_CMD_MODE				3	// switches camera modes
#define DRC_CMD_CAMERA				4	// set fixed camera
#define DRC_CMD_TIMESCALE			5	// sets time scale
#define DRC_CMD_MESSAGE				6	// send HUD centerprint
#define DRC_CMD_SOUND				7	// plays a particular sound
#define DRC_CMD_STATUS				8	// HLTV broadcast status
#define DRC_CMD_BANNER				9	// set GUI banner
#define DRC_CMD_STUFFTEXT			10	// like the normal svc_stufftext but as director command
#define DRC_CMD_CHASE				11	// chase a certain player
#define DRC_CMD_INEYE				12	// view player through own eyes
#define DRC_CMD_MAP					13	// show overview map
#define DRC_CMD_CAMPATH				14	// define camera waypoint
#define DRC_CMD_WAYPOINTS			15	// start moving camera, inetranl message

#define DRC_CMD_LAST				15


// DRC_CMD_EVENT event flags
#define DRC_FLAG_PRIO_MASK		0x0F	// priorities between 0 and 15 (15 most important)
#define DRC_FLAG_SIDE			(1<<4)	// 
#define DRC_FLAG_DRAMATIC		(1<<5)	// is a dramatic scene
#define DRC_FLAG_SLOWMOTION		(1<<6)  // would look good in SloMo
#define DRC_FLAG_FACEPLAYER		(1<<7)  // player is doning something (reload/defuse bomb etc)
#define DRC_FLAG_INTRO			(1<<8)	// is a introduction scene
#define DRC_FLAG_FINAL			(1<<9)	// is a final scene
#define DRC_FLAG_NO_RANDOM		(1<<10)	// don't randomize event data


// DRC_CMD_WAYPOINT flags
#define DRC_FLAG_STARTPATH		1	// end with speed 0.0
#define DRC_FLAG_SLOWSTART		2	// start with speed 0.0
#define DRC_FLAG_SLOWEND		4	// end with speed 0.0

// entity effects
#define EF_BRIGHTFIELD 1 // swirling cloud of particles
#define EF_MUZZLEFLASH 2 // single frame ELIGHT on entity attachment 0
#define EF_BRIGHTLIGHT 4 // DLIGHT centered at entity origin
#define EF_DIMLIGHT    8 // player flashlight
#define EF_INVLIGHT    16 // get lighting from ceiling
#define EF_NOINTERP    32 // don't interpolate the next frame
#define EF_LIGHT       64 // rocket flare glow sprite
#define EF_NODRAW      128 // don't draw entity
#define EF_NIGHTVISION 256 // player nightvision
#define EF_SNIPERLASER 512 // sniper laser effect
#define EF_FIBERCAMERA 1024 // fiber camera

// entity flags
#define EFLAG_SLERP 1 // do studio interpolation of this entity

//
// temp entity events
//
#define TE_BEAMPOINTS 0 // beam effect between two points
// coord coord coord (start position)
// coord coord coord (end position)
// short (sprite index)
// byte (starting frame)
// byte (frame rate in 0.1's)
// byte (life in 0.1's)
// byte (line width in 0.1's)
// byte (noise amplitude in 0.01's)
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

#define TE_BEAMENTPOINT 1 // beam effect between point and entity
// short (start entity)
// coord coord coord (end position)
// short (sprite index)
// byte (starting frame)
// byte (frame rate in 0.1's)
// byte (life in 0.1's)
// byte (line width in 0.1's)
// byte (noise amplitude in 0.01's)
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

#define TE_GUNSHOT 2 // particle effect plus ricochet sound
// coord coord coord (position)

#define TE_EXPLOSION 3 // additive sprite, 2 dynamic lights, flickering particles, explosion sound, move vertically 8 pps
// coord coord coord (position)
// short (sprite index)
// byte (scale in 0.1's)
// byte (framerate)
// byte (flags)
//
// The Explosion effect has some flags to control performance/aesthetic features:
#define TE_EXPLFLAG_NONE        0 // all flags clear makes default Half-Life explosion
#define TE_EXPLFLAG_NOADDITIVE  1 // sprite will be drawn opaque (ensure that the sprite you send is a non-additive sprite)
#define TE_EXPLFLAG_NODLIGHTS   2 // do not render dynamic lights
#define TE_EXPLFLAG_NOSOUND     4 // do not play client explosion sound
#define TE_EXPLFLAG_NOPARTICLES 8 // do not draw particles

#define TE_TAREXPLOSION 4 // Quake1 "tarbaby" explosion with sound
// coord coord coord (position)

#define TE_SMOKE 5 // alphablend sprite, move vertically 30 pps
// coord coord coord (position)
// short (sprite index)
// byte (scale in 0.1's)
// byte (framerate)

#define TE_TRACER 6 // tracer effect from point to point
// coord, coord, coord (start)
// coord, coord, coord (end)

#define TE_LIGHTNING 7 // TE_BEAMPOINTS with simplified parameters
// coord, coord, coord (start)
// coord, coord, coord (end)
// byte (life in 0.1's)
// byte (width in 0.1's)
// byte (amplitude in 0.01's)
// short (sprite model index)

#define TE_BEAMENTS 8
// short (start entity)
// short (end entity)
// short (sprite index)
// byte (starting frame)
// byte (frame rate in 0.1's)
// byte (life in 0.1's)
// byte (line width in 0.1's)
// byte (noise amplitude in 0.01's)
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

#define TE_SPARKS 9 // 8 random tracers with gravity, ricochet sprite
// coord coord coord (position)

#define TE_LAVASPLASH 10 // Quake1 lava splash
// coord coord coord (position)

#define TE_TELEPORT 11 // Quake1 teleport splash
// coord coord coord (position)

#define TE_EXPLOSION2 12 // Quake1 colormaped (base palette) particle explosion with sound
// coord coord coord (position)
// byte (starting color)
// byte (num colors)

#define TE_BSPDECAL 13 // Decal from the .BSP file
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// short (texture index of precached decal texture name)
// short (entity index)
// [optional - only included if previous short is non-zero (not the world)] short (index of model of above entity)

#define TE_IMPLOSION 14 // tracers moving toward a point
// coord, coord, coord (position)
// byte (radius)
// byte (count)
// byte (life in 0.1's)

#define TE_SPRITETRAIL 15 // line of moving glow sprites with gravity, fadeout, and collisions
// coord, coord, coord (start)
// coord, coord, coord (end)
// short (sprite index)
// byte (count)
// byte (life in 0.1's)
// byte (scale in 0.1's)
// byte (velocity along vector in 10's)
// byte (randomness of velocity in 10's)

#define TE_BEAM 16 // obsolete

#define TE_SPRITE 17 // additive sprite, plays 1 cycle
// coord, coord, coord (position)
// short (sprite index)
// byte (scale in 0.1's)
// byte (brightness)

#define TE_BEAMSPRITE 18 // A beam with a sprite at the end
// coord, coord, coord (start position)
// coord, coord, coord (end position)
// short (beam sprite index)
// short (end sprite index)

#define TE_BEAMTORUS 19 // screen aligned beam ring, expands to max radius over lifetime
// coord coord coord (center position)
// coord coord coord (axis and radius)
// short (sprite index)
// byte (starting frame)
// byte (frame rate in 0.1's)
// byte (life in 0.1's)
// byte (line width in 0.1's)
// byte (noise amplitude in 0.01's)
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

#define TE_BEAMDISK 20 // disk that expands to max radius over lifetime
// coord coord coord (center position)
// coord coord coord (axis and radius)
// short (sprite index)
// byte (starting frame)
// byte (frame rate in 0.1's)
// byte (life in 0.1's)
// byte (line width in 0.1's)
// byte (noise amplitude in 0.01's)
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

#define TE_BEAMCYLINDER 21 // cylinder that expands to max radius over lifetime
// coord coord coord (center position)
// coord coord coord (axis and radius)
// short (sprite index)
// byte (starting frame)
// byte (frame rate in 0.1's)
// byte (life in 0.1's)
// byte (line width in 0.1's)
// byte (noise amplitude in 0.01's)
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

#define TE_BEAMFOLLOW 22 // create a line of decaying beam segments until entity stops moving
// short (entity:attachment to follow)
// short (sprite index)
// byte (life in 0.1's)
// byte (line width in 0.1's)
// byte,byte,byte (color)
// byte (brightness)

#define TE_GLOWSPRITE 23
// coord, coord, coord (pos) short (model index) byte (scale / 10)

#define TE_BEAMRING 24 // connect a beam ring to two entities
// short (start entity)
// short (end entity)
// short (sprite index)
// byte (starting frame)
// byte (frame rate in 0.1's)
// byte (life in 0.1's)
// byte (line width in 0.1's)
// byte (noise amplitude in 0.01's)
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

#define TE_STREAK_SPLASH 25 // oriented shower of tracers
// coord coord coord (start position)
// coord coord coord (direction vector)
// byte (color)
// short (count)
// short (base speed)
// short (ramdon velocity)

#define TE_BEAMHOSE 26 // obsolete

#define TE_DLIGHT 27 // dynamic light, effect world, minor entity effect
// coord, coord, coord (pos)
// byte (radius in 10's)
// byte byte byte (color)
// byte (brightness)
// byte (life in 10's)
// byte (decay rate in 10's)

#define TE_ELIGHT 28 // point entity light, no world effect
// short (entity:attachment to follow)
// coord coord coord (initial position)
// coord (radius)
// byte byte byte (color)
// byte (life in 0.1's)
// coord (decay rate)

#define TE_TEXTMESSAGE 29
// short 1.2.13 x (-1 = center)
// short 1.2.13 y (-1 = center)
// byte Effect 0 = fade in/fade out
// 1 is flickery credits
// 2 is write out (training room)

// 4 bytes r,g,b,a color1	(text color)
// 4 bytes r,g,b,a color2	(effect color)
// ushort 8.8 fadein time
// ushort 8.8  fadeout time
// ushort 8.8 hold time
// optional ushort 8.8 fxtime	(time the highlight lags behing the leading text in effect 2)
// string text message		(512 chars max sz string)
#define TE_LINE 30
// coord, coord, coord		startpos
// coord, coord, coord		endpos
// short life in 0.1 s
// 3 bytes r, g, b

#define TE_BOX 31
// coord, coord, coord		boxmins
// coord, coord, coord		boxmaxs
// short life in 0.1 s
// 3 bytes r, g, b

#define TE_KILLBEAM 99 // kill all beams attached to entity
// short (entity)

#define TE_LARGEFUNNEL 100
// coord coord coord (funnel position)
// short (sprite index)
// short (flags)

#define TE_BLOODSTREAM 101 // particle spray
// coord coord coord (start position)
// coord coord coord (spray vector)
// byte (color)
// byte (speed)

#define TE_SHOWLINE 102 // line of particles every 5 units, dies in 30 seconds
// coord coord coord (start position)
// coord coord coord (end position)

#define TE_BLOOD 103 // particle spray
// coord coord coord (start position)
// coord coord coord (spray vector)
// byte (color)
// byte (speed)

#define TE_DECAL 104 // Decal applied to a brush entity (not the world)
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// byte (texture index of precached decal texture name)
// short (entity index)

#define TE_FIZZ 105 // create alpha sprites inside of entity, float upwards
// short (entity)
// short (sprite index)
// byte (density)

#define TE_MODEL 106 // create a moving model that bounces and makes a sound when it hits
// coord, coord, coord (position)
// coord, coord, coord (velocity)
// angle (initial yaw)
// short (model index)
// byte (bounce sound type)
// byte (life in 0.1's)

#define TE_EXPLODEMODEL 107 // spherical shower of models, picks from set
// coord, coord, coord (origin)
// coord (velocity)
// short (model index)
// short (count)
// byte (life in 0.1's)

#define TE_BREAKMODEL 108 // box of models or sprites
// coord, coord, coord (position)
// coord, coord, coord (size)
// coord, coord, coord (velocity)
// byte (random velocity in 10's)
// short (sprite or model index)
// byte (count)
// byte (life in 0.1 secs)
// byte (flags)

#define TE_GUNSHOTDECAL 109 // decal and ricochet sound
// coord, coord, coord (position)
// short (entity index???)
// byte (decal???)

#define TE_SPRITE_SPRAY 110 // spay of alpha sprites
// coord, coord, coord (position)
// coord, coord, coord (velocity)
// short (sprite index)
// byte (count)
// byte (speed)
// byte (noise)

#define TE_ARMOR_RICOCHET 111 // quick spark sprite, client ricochet sound.
// coord, coord, coord (position)
// byte (scale in 0.1's)

#define TE_PLAYERDECAL 112 // ???
// byte (playerindex)
// coord, coord, coord (position)
// short (entity???)
// byte (decal number???)
// [optional] short (model index???)

#define TE_BUBBLES 113 // create alpha sprites inside of box, float upwards
// coord, coord, coord (min start position)
// coord, coord, coord (max start position)
// coord (float height)
// short (model index)
// byte (count)
// coord (speed)

#define TE_BUBBLETRAIL 114 // create alpha sprites along a line, float upwards
// coord, coord, coord (min start position)
// coord, coord, coord (max start position)
// coord (float height)
// short (model index)
// byte (count)
// coord (speed)

#define TE_BLOODSPRITE 115 // spray of opaque sprite1's that fall, single sprite2 for 1..2 secs (this is a high-priority tent)
// coord, coord, coord (position)
// short (sprite1 index)
// short (sprite2 index)
// byte (color)
// byte (scale)

#define TE_WORLDDECAL 116 // Decal applied to the world brush
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// byte (texture index of precached decal texture name)

#define TE_WORLDDECALHIGH 117 // Decal (with texture index > 256) applied to world brush
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// byte (texture index of precached decal texture name - 256)

#define TE_DECALHIGH 118 // Same as TE_DECAL, but the texture index was greater than 256
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// byte (texture index of precached decal texture name - 256)
// short (entity index)

#define TE_PROJECTILE 119 // Makes a projectile (like a nail) (this is a high-priority tent)
// coord, coord, coord (position)
// coord, coord, coord (velocity)
// short (modelindex)
// byte (life)
// byte (owner)  projectile won't collide with owner (if owner == 0, projectile will hit any client).

#define TE_SPRAY 120 // Throws a shower of sprites or models
// coord, coord, coord (position)
// coord, coord, coord (direction)
// short (modelindex)
// byte (count)
// byte (speed)
// byte (noise)
// byte (rendermode)

#define TE_PLAYERSPRITES 121 // sprites emit from a player's bounding box (ONLY use for players!)
// byte (playernum)
// short (sprite modelindex)
// byte (count)
// byte (variance) (0 = no variance in size) (10 = 10% variance in size)

#define TE_PARTICLEBURST 122 // very similar to lavasplash.
// coord (origin)
// short (radius)
// byte (particle color)
// byte (duration * 10) (will be randomized a bit)

#define TE_FIREFIELD 123 // makes a field of fire.
// coord (origin)
// short (radius) (fire is made in a square around origin. -radius, -radius to radius, radius)
// short (modelindex)
// byte (count)
// byte (flags)
// byte (duration (in seconds) * 10) (will be randomized a bit)
//
// to keep network traffic low, this message has associated flags that fit into a byte:
#define TEFIRE_FLAG_ALLFLOAT  1 // all sprites will drift upwards as they animate
#define TEFIRE_FLAG_SOMEFLOAT 2 // some of the sprites will drift upwards. (50% chance)
#define TEFIRE_FLAG_LOOP      4 // if set, sprite plays at 15 fps, otherwise plays at whatever rate stretches the animation over the sprite's duration.
#define TEFIRE_FLAG_ALPHA     8 // if set, sprite is rendered alpha blended at 50% else, opaque
#define TEFIRE_FLAG_PLANAR    16 // if set, all fire sprites have same initial Z instead of randomly filling a cube.
#define TEFIRE_FLAG_ADDITIVE  32 // if set, sprite is rendered non-opaque with additive

#define TE_PLAYERATTACHMENT 124 // attaches a TENT to a player (this is a high-priority tent)
// byte (entity index of player)
// coord (vertical offset) ( attachment origin.z = player origin.z + vertical offset )
// short (model index)
// short (life * 10 );

#define TE_KILLPLAYERATTACHMENTS 125 // will expire all TENTS attached to a player.
// byte (entity index of player)

#define TE_MULTIGUNSHOT 126 // much more compact shotgun message
// This message is used to make a client approximate a 'spray' of gunfire.
// Any weapon that fires more than one bullet per frame and fires in a bit of a spread is
// a good candidate for MULTIGUNSHOT use. (shotguns)
//
// NOTE: This effect makes the client do traces for each bullet, these client traces ignore
//		 entities that have studio models.Traces are 4096 long.
//
// coord (origin)
// coord (origin)
// coord (origin)
// coord (direction)
// coord (direction)
// coord (direction)
// coord (x noise * 100)
// coord (y noise * 100)
// byte (count)
// byte (bullethole decal texture index)

#define TE_USERTRACER 127 // larger message than the standard tracer, but allows some customization.
// coord (origin)
// coord (origin)
// coord (origin)
// coord (velocity)
// coord (velocity)
// coord (velocity)
// byte ( life * 10 )
// byte ( color ) this is an index into an array of color vectors in the engine. (0 - )
// byte ( length * 10 )

#define MSG_BROADCAST      0 // unreliable to all
#define MSG_ONE            1 // reliable to one (msg_entity)
#define MSG_ALL            2 // reliable to all
#define MSG_INIT           3 // write to the init string
#define MSG_PVS            4 // Ents in PVS of org
#define MSG_PAS            5 // Ents in PAS of org
#define MSG_PVS_R          6 // Reliable to PVS
#define MSG_PAS_R          7 // Reliable to PAS
#define MSG_ONE_UNRELIABLE 8 // Send to one client, but don't put in reliable stream, put in unreliable datagram ( could be dropped )
#define MSG_SPEC           9 // Sends to all spectator proxies

// contents of a spot in the world
#define CONTENTS_EMPTY -1
#define CONTENTS_SOLID -2
#define CONTENTS_WATER -3
#define CONTENTS_SLIME -4
#define CONTENTS_LAVA  -5
#define CONTENTS_SKY   -6
/* These additional contents constants are defined in bspfile.h
#define	CONTENTS_ORIGIN		-7		// removed at csg time
#define	CONTENTS_CLIP		-8		// changed to contents_solid
#define	CONTENTS_CURRENT_0		-9
#define	CONTENTS_CURRENT_90		-10
#define	CONTENTS_CURRENT_180	-11
#define	CONTENTS_CURRENT_270	-12
#define	CONTENTS_CURRENT_UP		-13
#define	CONTENTS_CURRENT_DOWN	-14
#define CONTENTS_TRANSLUCENT	-15
*/
#define CONTENTS_LADDER -16

#define CONTENT_FLYFIELD         -17
#define CONTENT_GRAVITY_FLYFIELD -18
#define CONTENT_FOG              -19

#define CONTENT_EMPTY -1
#define CONTENT_SOLID -2
#define CONTENT_WATER -3
#define CONTENT_SLIME -4
#define CONTENT_LAVA  -5
#define CONTENT_SKY   -6

// channels
#define CHAN_AUTO              0
#define CHAN_WEAPON            1
#define CHAN_VOICE             2
#define CHAN_ITEM              3
#define CHAN_BODY              4
#define CHAN_STREAM            5 // allocate stream channel from the static or dynamic area
#define CHAN_STATIC            6 // allocate channel from the static area
#define CHAN_NETWORKVOICE_BASE 7 // voice data coming across the network
#define CHAN_NETWORKVOICE_END  500 // network voice data reserves slots (CHAN_NETWORKVOICE_BASE through CHAN_NETWORKVOICE_END).
#define CHAN_BOT               501 // channel used for bot chatter.

// attenuation values
#define ATTN_NONE   0
#define ATTN_NORM   (float)0.8
#define ATTN_IDLE   (float)2
#define ATTN_STATIC (float)1.25

// pitch values
#define PITCH_NORM 100 // non-pitch shifted
#define PITCH_LOW  95 // other values are possible - 0-255, where 255 is very high
#define PITCH_HIGH 120

// volume values
#define VOL_NORM 1.0

// plats
#define PLAT_LOW_TRIGGER 1

// Trains
#define SF_TRAIN_WAIT_RETRIGGER 1
#define SF_TRAIN_START_ON       4 // Train is initially moving
#define SF_TRAIN_PASSABLE       8 // Train is not solid -- used to make water trains

// Break Model Defines

#define BREAK_TYPEMASK 0x4F
#define BREAK_GLASS    0x01
#define BREAK_METAL    0x02
#define BREAK_FLESH    0x04
#define BREAK_WOOD     0x08

#define BREAK_SMOKE    0x10
#define BREAK_TRANS    0x20
#define BREAK_CONCRETE 0x40
#define BREAK_2        0x80

// Colliding temp entity sounds

#define BOUNCE_GLASS     BREAK_GLASS
#define BOUNCE_METAL     BREAK_METAL
#define BOUNCE_FLESH     BREAK_FLESH
#define BOUNCE_WOOD      BREAK_WOOD
#define BOUNCE_SHRAP     0x10
#define BOUNCE_SHELL     0x20
#define BOUNCE_CONCRETE  BREAK_CONCRETE
#define BOUNCE_SHOTSHELL 0x80

// Temp entity bounce sound types
#define TE_BOUNCE_NULL      0
#define TE_BOUNCE_SHELL     1
#define TE_BOUNCE_SHOTSHELL 2

// Rendering constants
enum
{
	kRenderNormal, // src
	kRenderTransColor, // c*a+dest*(1-a)
	kRenderTransTexture, // src*a+dest*(1-a)
	kRenderGlow, // src*a+dest -- No Z buffer checks
	kRenderTransAlpha, // src*srca+dest*(1-srca)
	kRenderTransAdd, // src*a+dest
};

enum
{
	kRenderFxNone = 0,
	kRenderFxPulseSlow,
	kRenderFxPulseFast,
	kRenderFxPulseSlowWide,
	kRenderFxPulseFastWide,
	kRenderFxFadeSlow,
	kRenderFxFadeFast,
	kRenderFxSolidSlow,
	kRenderFxSolidFast,
	kRenderFxStrobeSlow,
	kRenderFxStrobeFast,
	kRenderFxStrobeFaster,
	kRenderFxFlickerSlow,
	kRenderFxFlickerFast,
	kRenderFxNoDissipation,
	kRenderFxDistort, // Distort/scale/translate flicker
	kRenderFxHologram, // kRenderFxDistort + distance fade
	kRenderFxDeadPlayer, // kRenderAmt is the player index
	kRenderFxExplode, // Scale up really big!
	kRenderFxGlowShell, // Glowing Shell
	kRenderFxClampMinScale, // Keep this sprite from getting very small (SPRITES only!)
	kRenderFxLightMultiplier, //CTM !!!CZERO added to tell the studiorender that the value in iuser2 is a lightmultiplier
};

typedef unsigned char byte;
typedef unsigned short word;
#define _DEF_BYTE_

#ifndef __cplusplus
typedef enum
{
	false,
	true
} qboolean;
#else
typedef int qboolean;
#endif

typedef struct
{
	Vector normal;
	float dist;
} plane_t;

typedef struct usercmd_s
{
	short	lerp_msec;      // Interpolation time on client
	byte	msec;           // Duration in ms of command
	vec3_t	viewangles;     // Command view angles.

// intended velocities
	float	forwardmove;    // Forward velocity.
	float	sidemove;       // Sideways velocity.
	float	upmove;         // Upward velocity.
	byte	lightlevel;     // Light level at spot where we are standing.
	unsigned short  buttons;  // Attack buttons
	byte    impulse;          // Impulse command issued.
	byte	weaponselect;	// Current weapon id

// Experimental player impact stuff.
	int		impact_index;
	vec3_t	impact_position;
} usercmd_t;

// physent_t
typedef struct physent_s
{
	char			name[32];             // Name of model, or "player" or "world".
	int				player;
	vec3_t			origin;               // Model's origin in world coordinates.
	struct model_s* model;		          // only for bsp models
	struct model_s* studiomodel;         // SOLID_BBOX, but studio clip intersections.
	vec3_t			mins, maxs;	          // only for non-bsp models
	int				info;		          // For client or server to use to identify (index into edicts or cl_entities)
	vec3_t			angles;               // rotated entities need this info for hull testing to work.

	int				solid;				  // Triggers and func_door type WATER brushes are SOLID_NOT
	int				skin;                 // BSP Contents for such things like fun_door water brushes.
	int				rendermode;			  // So we can ignore glass

	// Complex collision detection.
	float			frame;
	int				sequence;
	byte			controller[4];
	byte			blending[2];

	int				movetype;
	int				takedamage;
	int				blooddecal;
	int				team;
	int				classnumber;

	// For mods
	int				iuser1;
	int				iuser2;
	int				iuser3;
	int				iuser4;
	float			fuser1;
	float			fuser2;
	float			fuser3;
	float			fuser4;
	vec3_t			vuser1;
	vec3_t			vuser2;
	vec3_t			vuser3;
	vec3_t			vuser4;
} physent_t;

#define	MAX_PHYSENTS 600 		  // Must have room for all entities in the world.
#define MAX_MOVEENTS 64
#define	MAX_CLIP_PLANES	5

#define PM_NORMAL			0x00000000
#define PM_STUDIO_IGNORE	0x00000001		// Skip studio models
#define PM_STUDIO_BOX		0x00000002		// Use boxes for non-complex studio models (even in traceline)
#define PM_GLASS_IGNORE		0x00000004		// Ignore entities with non-normal rendermode
#define PM_WORLD_ONLY		0x00000008		// Only trace against the world

// Values for flags parameter of PM_TraceLine
#define PM_TRACELINE_ANYVISIBLE		0
#define PM_TRACELINE_PHYSENTSONLY	1

typedef struct
{
	vec3_t	normal;
	float	dist;
} pmplane_t;

#define IN_ATTACK	(1 << 0)
#define IN_JUMP		(1 << 1)
#define IN_DUCK		(1 << 2)
#define IN_FORWARD	(1 << 3)
#define IN_BACK		(1 << 4)
#define IN_USE		(1 << 5)
#define IN_CANCEL	(1 << 6)
#define IN_LEFT		(1 << 7)
#define IN_RIGHT	(1 << 8)
#define IN_MOVELEFT	(1 << 9)
#define IN_MOVERIGHT (1 << 10)
#define IN_ATTACK2	(1 << 11)
#define IN_RUN      (1 << 12)
#define IN_RELOAD	(1 << 13)
#define IN_ALT1		(1 << 14)
#define IN_SCORE	(1 << 15)   // Used by client.dll for when scoreboard is held down

typedef struct pmtrace_s pmtrace_t;

struct pmtrace_s
{
	qboolean	allsolid;	      // if true, plane is not valid
	qboolean	startsolid;	      // if true, the initial point was in a solid area
	qboolean	inopen, inwater;  // End point is in empty space or in water
	float		fraction;		  // time completed, 1.0 = didn't hit anything
	vec3_t		endpos;			  // final position
	pmplane_t	plane;		      // surface normal at impact
	int			ent;			  // entity at impact
	vec3_t      deltavelocity;    // Change in player's velocity caused by impact.  
								  // Only run on server.
	int         hitgroup;
};

// FUNC
typedef int(*pfnUserMsgHook)	(const char* pszName, int iSize, void* pbuf);

typedef struct rect_s
{
	int				left, right, top, bottom;
} wrect_t;

typedef struct cvar_s
{
	char* name;
	char* string;
	int        flags;
	float    value;
	struct cvar_s* next;
} cvar_t;

typedef struct SCREENINFO_s
{
	int		iSize;
	int		iWidth;
	int		iHeight;
	int		iFlags;
	int		iCharHeight;
	short	charWidths[256];
} SCREENINFO;

typedef struct client_data_s
{
	// fields that cannot be modified  (ie. have no effect if changed)
	vec3_t origin;

	// fields that can be changed by the cldll
	vec3_t viewangles;
	int		iWeaponBits;
	float	fov;	// field of view
} client_data_t;

typedef int HSPRITE_HL;	// handle to a graphic

typedef struct client_sprite_s
{
	char szName[64];
	char szSprite[64];
	int hspr;
	int iRes;
	wrect_t rc;
} client_sprite_t;

typedef struct client_textmessage_s
{
	int		effect;
	byte	r1, g1, b1, a1;		// 2 colors for effects
	byte	r2, g2, b2, a2;
	float	x;
	float	y;
	float	fadein;
	float	fadeout;
	float	holdtime;
	float	fxtime;
	const char* pName;
	const char* pMessage;
} client_textmessage_t;

typedef struct hud_player_info_s
{
	char* name;
	short ping;
	byte thisplayer;  // TRUE if this is the calling player

  // stuff that's unused at the moment,  but should be done
	byte spectator;
	byte packetloss;

	char* model;
	short topcolor;
	short bottomcolor;

} hud_player_info_t;

typedef struct ref_params_s
{
	// Output
	float	vieworg[3];
	float	viewangles[3];

	float	forward[3];
	float	right[3];
	float   up[3];

	// Client frametime;
	float	frametime;
	// Client time
	float	time;

	// Misc
	int		intermission;
	int		paused;
	int		spectator;
	int		onground;
	int		waterlevel;

	float	simvel[3];
	float	simorg[3];

	float	viewheight[3];
	float	idealpitch;

	float	cl_viewangles[3];

	int		health;
	float	crosshairangle[3];
	float	viewsize;

	float	punchangle[3];
	int		maxclients;
	int		viewentity;
	int		playernum;
	int		max_entities;
	int		demoplayback;
	int		hardware;

	int		smoothing;

	// Last issued usercmd
	struct usercmd_s* cmd;

	// Movevars
	struct movevars_s* movevars;

	int		viewport[4];		// the viewport coordinates x ,y , width, height

	int		nextView;			// the renderer calls ClientDLL_CalcRefdef() and Renderview
								// so long in cycles until this value is 0 (multiple views)
	int		onlyClientDraw;		// if !=0 nothing is drawn by the engine except clientDraw functions
} ref_params_t;

typedef struct link_s
{
	struct link_s* prev, * next;
} link_t;

typedef struct edict_s edict_t;
typedef int	string_t;

typedef struct entvars_s
{
	string_t	classname;
	string_t	globalname;

	vec3_t		origin;
	vec3_t		oldorigin;
	vec3_t		velocity;
	vec3_t		basevelocity;
	vec3_t      clbasevelocity;  // Base velocity that was passed in to server physics so 
								 //  client can predict conveyors correctly.  Server zeroes it, so we need to store here, too.
	vec3_t		movedir;

	vec3_t		angles;			// Model angles
	vec3_t		avelocity;		// angle velocity (degrees per second)
	vec3_t		punchangle;		// auto-decaying view angle adjustment
	vec3_t		v_angle;		// Viewing angle (player only)

	// For parametric entities
	vec3_t		endpos;
	vec3_t		startpos;
	float		impacttime;
	float		starttime;

	int			fixangle;		// 0:nothing, 1:force view angles, 2:add avelocity
	float		idealpitch;
	float		pitch_speed;
	float		ideal_yaw;
	float		yaw_speed;

	int			modelindex;
	string_t	model;

	int			viewmodel;		// player's viewmodel
	int			weaponmodel;	// what other players see

	vec3_t		absmin;		// BB max translated to world coord
	vec3_t		absmax;		// BB max translated to world coord
	vec3_t		mins;		// local BB min
	vec3_t		maxs;		// local BB max
	vec3_t		size;		// maxs - mins

	float		ltime;
	float		nextthink;

	int			movetype;
	int			solid;

	int			skin;
	int			body;			// sub-model selection for studiomodels
	int 		effects;

	float		gravity;		// % of "normal" gravity
	float		friction;		// inverse elasticity of MOVETYPE_BOUNCE

	int			light_level;

	int			sequence;		// animation sequence
	int			gaitsequence;	// movement animation sequence for player (0 for none)
	float		frame;			// % playback position in animation sequences (0..255)
	float		animtime;		// world time when frame was set
	float		framerate;		// animation playback rate (-8x to 8x)
	byte		controller[4];	// bone controller setting (0..255)
	byte		blending[2];	// blending amount between sub-sequences (0..255)

	float		scale;			// sprite rendering scale (0..255)

	int			rendermode;
	float		renderamt;
	vec3_t		rendercolor;
	int			renderfx;

	float		health;
	float		frags;
	int			weapons;  // bit mask for available weapons
	float		takedamage;

	int			deadflag;
	vec3_t		view_ofs;	// eye position

	int			button;
	int			impulse;

	edict_t* chain;			// Entity pointer when linked into a linked list
	edict_t* dmg_inflictor;
	edict_t* enemy;
	edict_t* aiment;		// entity pointer when MOVETYPE_FOLLOW
	edict_t* owner;
	edict_t* groundentity;

	int			spawnflags;
	int			flags;

	int			colormap;		// lowbyte topcolor, highbyte bottomcolor
	int			team;

	float		max_health;
	float		teleport_time;
	float		armortype;
	float		armorvalue;
	int			waterlevel;
	int			watertype;

	string_t	target;
	string_t	targetname;
	string_t	netname;
	string_t	message;

	float		dmg_take;
	float		dmg_save;
	float		dmg;
	float		dmgtime;

	string_t	noise;
	string_t	noise1;
	string_t	noise2;
	string_t	noise3;

	float		speed;
	float		air_finished;
	float		pain_finished;
	float		radsuit_finished;

	edict_t* pContainingEntity;

	int			playerclass;
	float		maxspeed;

	float		fov;
	int			weaponanim;

	int			pushmsec;

	int			bInDuck;
	int			flTimeStepSound;
	int			flSwimTime;
	int			flDuckTime;
	int			iStepLeft;
	float		flFallVelocity;

	int			gamestate;

	int			oldbuttons;

	int			groupinfo;

	// For mods
	int			iuser1;
	int			iuser2;
	int			iuser3;
	int			iuser4;
	float		fuser1;
	float		fuser2;
	float		fuser3;
	float		fuser4;
	vec3_t		vuser1;
	vec3_t		vuser2;
	vec3_t		vuser3;
	vec3_t		vuser4;
	edict_t* euser1;
	edict_t* euser2;
	edict_t* euser3;
	edict_t* euser4;
} entvars_t;

#define	MAX_ENT_LEAFS	48

struct edict_s
{
	qboolean	free;
	int			serialnumber;
	link_t		area;				// linked to a division node or leaf

	int			headnode;			// -1 to use normal leaf check
	int			num_leafs;
	short		leafnums[MAX_ENT_LEAFS];

	float		freetime;			// sv.time when the object was freed

	void* pvPrivateData;		// Alloced and freed by engine, used by DLLs

	entvars_t	v;					// C exported fields from progs

	// other fields from progs come immediately after
};

typedef struct
{
	qboolean allsolid; // if true, plane is not valid
	qboolean startsolid; // if true, the initial point was in a solid area
	qboolean inopen, inwater;
	float fraction; // time completed, 1.0 = didn't hit anything
	Vector endpos; // final position
	plane_t plane; // surface normal at impact
	edict_t* ent; // entity the surface is on
	int hitgroup; // 0 == generic, non zero is specific body part
} trace_t;


typedef struct
{
	byte r, g, b;
} color24;

typedef struct
{
	unsigned r, g, b, a;
} colorVec;

typedef struct entity_state_s entity_state_t;

struct entity_state_s
{
	// Fields which are filled in by routines outside of delta compression
	int			entityType;
	// Index into cl_entities array for this entity.
	int			number;
	float		msg_time;

	// Message number last time the player/entity state was updated.
	int			messagenum;

	// Fields which can be transitted and reconstructed over the network stream
	vec3_t		origin;
	vec3_t		angles;

	int			modelindex;
	int			sequence;
	float		frame;
	int			colormap;
	short		skin;
	short		solid;
	int			effects;
	float		scale;

	byte		eflags;

	// Render information
	int			rendermode;
	int			renderamt;
	color24		rendercolor;
	int			renderfx;

	int			movetype;
	float		animtime;
	float		framerate;
	int			body;
	byte		controller[4];
	byte		blending[4];
	vec3_t		velocity;

	// Send bbox down to client for use during prediction.
	vec3_t		mins;
	vec3_t		maxs;

	int			aiment;
	// If owned by a player, the index of that player ( for projectiles ).
	int			owner;

	// Friction, for prediction.
	float		friction;
	// Gravity multiplier
	float		gravity;

	// PLAYER SPECIFIC
	int			team;
	int			playerclass;
	int			health;
	qboolean	spectator;
	int         weaponmodel;
	int			gaitsequence;
	// If standing on conveyor, e.g.
	vec3_t		basevelocity;
	// Use the crouched hull, or the regular player hull.
	int			usehull;
	// Latched buttons last time state updated.
	int			oldbuttons;
	// -1 = in air, else pmove entity number
	int			onground;
	int			iStepLeft;
	// How fast we are falling
	float		flFallVelocity;

	float		fov;
	int			weaponanim;

	// Parametric movement overrides
	vec3_t				startpos;
	vec3_t				endpos;
	float				impacttime;
	float				starttime;

	// For mods
	int			iuser1;
	int			iuser2;
	int			iuser3;
	int			iuser4;
	float		fuser1;
	float		fuser2;
	float		fuser3;
	float		fuser4;
	vec3_t		vuser1;
	vec3_t		vuser2;
	vec3_t		vuser3;
	vec3_t		vuser4;
};

typedef struct efrag_s
{
	struct mleaf_s* leaf;
	struct efrag_s* leafnext;
	struct cl_entity_s* entity;
	struct efrag_s* entnext;
} efrag_t;

typedef struct
{
	byte					mouthopen;		// 0 = mouth closed, 255 = mouth agape
	byte					sndcount;		// counter for running average
	int						sndavg;			// running average
} mouth_t;

typedef struct
{
	float					prevanimtime;
	float					sequencetime;
	byte					prevseqblending[2];
	vec3_t					prevorigin;
	vec3_t					prevangles;

	int						prevsequence;
	float					prevframe;

	byte					prevcontroller[4];
	byte					prevblending[2];
} latchedvars_t;

typedef struct
{
	// Time stamp for this movement
	float					animtime;

	vec3_t					origin;
	vec3_t					angles;
} position_history_t;

#define HISTORY_MAX		64  // Must be power of 2

typedef struct cl_entity_s cl_entity_t;

struct cl_entity_s
{
	int						index;      // Index into cl_entities ( should match actual slot, but not necessarily )

	qboolean				player;     // True if this entity is a "player"

	entity_state_t			baseline;   // The original state from which to delta during an uncompressed message
	entity_state_t			prevstate;  // The state information from the penultimate message received from the server
	entity_state_t			curstate;   // The state information from the last message received from server

	int						current_position;  // Last received history update index
	position_history_t		ph[HISTORY_MAX];   // History of position and angle updates for this player

	mouth_t					mouth;			// For synchronizing mouth movements.

	latchedvars_t			latched;		// Variables used by studio model rendering routines

	// Information based on interplocation, extrapolation, prediction, or just copied from last msg received.
	//
	float					lastmove;

	// Actual render position and angles
	vec3_t					origin;
	vec3_t					angles;

	// Attachment points
	vec3_t					attachment[4];

	// Other entity local information
	int						trivial_accept;

	struct model_s* model;			// cl.model_precache[ curstate.modelindes ];  all visible entities have a model
	struct efrag_s* efrag;			// linked list of efrags
	struct mnode_s* topnode;		// for bmodels, first world node that splits bmodel, or NULL if not split

	float					syncbase;		// for client-side animations -- used by obsolete alias animation system, remove?
	int						visframe;		// last frame this entity was found in an active leaf
	colorVec				cvFloorColor;
};

//--------------------------------------------------------------------------
// sequenceDefaultBits_e
//	
// Enumerated list of possible modifiers for a command.  This enumeration
// is used in a bitarray controlling what modifiers are specified for a command.
//---------------------------------------------------------------------------
enum sequenceModifierBits
{
	SEQUENCE_MODIFIER_EFFECT_BIT = (1 << 1),
	SEQUENCE_MODIFIER_POSITION_BIT = (1 << 2),
	SEQUENCE_MODIFIER_COLOR_BIT = (1 << 3),
	SEQUENCE_MODIFIER_COLOR2_BIT = (1 << 4),
	SEQUENCE_MODIFIER_FADEIN_BIT = (1 << 5),
	SEQUENCE_MODIFIER_FADEOUT_BIT = (1 << 6),
	SEQUENCE_MODIFIER_HOLDTIME_BIT = (1 << 7),
	SEQUENCE_MODIFIER_FXTIME_BIT = (1 << 8),
	SEQUENCE_MODIFIER_SPEAKER_BIT = (1 << 9),
	SEQUENCE_MODIFIER_LISTENER_BIT = (1 << 10),
	SEQUENCE_MODIFIER_TEXTCHANNEL_BIT = (1 << 11),
};
typedef enum sequenceModifierBits sequenceModifierBits_e;


//---------------------------------------------------------------------------
// sequenceCommandEnum_e
// 
// Enumerated sequence command types.
//---------------------------------------------------------------------------
enum sequenceCommandEnum_
{
	SEQUENCE_COMMAND_ERROR = -1,
	SEQUENCE_COMMAND_PAUSE = 0,
	SEQUENCE_COMMAND_FIRETARGETS,
	SEQUENCE_COMMAND_KILLTARGETS,
	SEQUENCE_COMMAND_TEXT,
	SEQUENCE_COMMAND_SOUND,
	SEQUENCE_COMMAND_GOSUB,
	SEQUENCE_COMMAND_SENTENCE,
	SEQUENCE_COMMAND_REPEAT,
	SEQUENCE_COMMAND_SETDEFAULTS,
	SEQUENCE_COMMAND_MODIFIER,
	SEQUENCE_COMMAND_POSTMODIFIER,
	SEQUENCE_COMMAND_NOOP,

	SEQUENCE_MODIFIER_EFFECT,
	SEQUENCE_MODIFIER_POSITION,
	SEQUENCE_MODIFIER_COLOR,
	SEQUENCE_MODIFIER_COLOR2,
	SEQUENCE_MODIFIER_FADEIN,
	SEQUENCE_MODIFIER_FADEOUT,
	SEQUENCE_MODIFIER_HOLDTIME,
	SEQUENCE_MODIFIER_FXTIME,
	SEQUENCE_MODIFIER_SPEAKER,
	SEQUENCE_MODIFIER_LISTENER,
	SEQUENCE_MODIFIER_TEXTCHANNEL,
};
typedef enum sequenceCommandEnum_ sequenceCommandEnum_e;


//---------------------------------------------------------------------------
// sequenceCommandType_e
// 
// Typeerated sequence command types.
//---------------------------------------------------------------------------
enum sequenceCommandType_
{
	SEQUENCE_TYPE_COMMAND,
	SEQUENCE_TYPE_MODIFIER,
};
typedef enum sequenceCommandType_ sequenceCommandType_e;


//---------------------------------------------------------------------------
// sequenceCommandMapping_s
// 
// A mapping of a command enumerated-value to its name.
//---------------------------------------------------------------------------
typedef struct sequenceCommandMapping_ sequenceCommandMapping_s;
struct sequenceCommandMapping_
{
	sequenceCommandEnum_e	commandEnum;
	const char* commandName;
	sequenceCommandType_e	commandType;
};


//---------------------------------------------------------------------------
// sequenceCommandLine_s
// 
// Structure representing a single command (usually 1 line) from a
//	.SEQ file entry.
//---------------------------------------------------------------------------
typedef struct sequenceCommandLine_ sequenceCommandLine_s;
struct sequenceCommandLine_
{
	int						commandType;		// Specifies the type of command
	client_textmessage_t	clientMessage;		// Text HUD message struct
	char* speakerName;		// Targetname of speaking entity
	char* listenerName;		// Targetname of entity being spoken to
	char* soundFileName;		// Name of sound file to play
	char* sentenceName;		// Name of sentences.txt to play
	char* fireTargetNames;	// List of targetnames to fire
	char* killTargetNames;	// List of targetnames to remove
	float					delay;				// Seconds 'till next command
	int						repeatCount;		// If nonzero, reset execution pointer to top of block (N times, -1 = infinite)
	int						textChannel;		// Display channel on which text message is sent
	int						modifierBitField;	// Bit field to specify what clientmessage fields are valid
	sequenceCommandLine_s* nextCommandLine;	// Next command (linked list)
};


//---------------------------------------------------------------------------
// sequenceEntry_s
// 
// Structure representing a single command (usually 1 line) from a
//	.SEQ file entry.
//---------------------------------------------------------------------------
typedef struct sequenceEntry_ sequenceEntry_s;
struct sequenceEntry_
{
	char* fileName;		// Name of sequence file without .SEQ extension
	char* entryName;		// Name of entry label in file
	sequenceCommandLine_s* firstCommand;	// Linked list of commands in entry
	sequenceEntry_s* nextEntry;		// Next loaded entry
	qboolean				isGlobal;		// Is entry retained over level transitions?
};



//---------------------------------------------------------------------------
// sentenceEntry_s
// Structure representing a single sentence of a group from a .SEQ
// file entry.  Sentences are identical to entries in sentences.txt, but
// can be unique per level and are loaded/unloaded with the level.
//---------------------------------------------------------------------------
typedef struct sentenceEntry_ sentenceEntry_s;
struct sentenceEntry_
{
	char* data;			// sentence data (ie "We have hostiles" )
	sentenceEntry_s* nextEntry;		// Next loaded entry
	qboolean				isGlobal;		// Is entry retained over level transitions?
	unsigned int			index;			// this entry's position in the file.
};

//--------------------------------------------------------------------------
// sentenceGroupEntry_s
// Structure representing a group of sentences found in a .SEQ file.
// A sentence group is defined by all sentences with the same name, ignoring
// the number at the end of the sentence name.  Groups enable a sentence
// to be picked at random across a group.
//--------------------------------------------------------------------------
typedef struct sentenceGroupEntry_ sentenceGroupEntry_s;
struct sentenceGroupEntry_
{
	char* groupName;		// name of the group (ie CT_ALERT )
	unsigned int			numSentences;	// number of sentences in group
	sentenceEntry_s* firstSentence;	// head of linked list of sentences in group
	sentenceGroupEntry_s* nextEntry;		// next loaded group
};

typedef __int16 int16;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;

#define	MAX_ALIAS_NAME	32

typedef struct cmdalias_s
{
	struct cmdalias_s* next;
	char	name[MAX_ALIAS_NAME];
	char* value;
} cmdalias_t;

/*
==============================================================================
STUDIO MODELS
Studio models are position independent, so the cache manager can move them.
==============================================================================
*/


#define MAXSTUDIOTRIANGLES	20000	// TODO: tune this
#define MAXSTUDIOVERTS		2048	// TODO: tune this
#define MAXSTUDIOSEQUENCES	2048	// total animation sequences -- KSH incremented
#define MAXSTUDIOSKINS		100		// total textures
#define MAXSTUDIOSRCBONES	512		// bones allowed at source movement
#define MAXSTUDIOBONES		128		// total bones actually used
#define MAXSTUDIOMODELS		32		// sub-models per model
#define MAXSTUDIOBODYPARTS	32
#define MAXSTUDIOGROUPS		16
#define MAXSTUDIOANIMATIONS	2048		
#define MAXSTUDIOMESHES		256
#define MAXSTUDIOEVENTS		1024
#define MAXSTUDIOPIVOTS		256
#define MAXSTUDIOCONTROLLERS 8

typedef struct
{
	int					id;
	int					version;

	char				name[64];
	int					length;

	vec3_t				eyeposition;	// ideal eye position
	vec3_t				min;			// ideal movement hull size
	vec3_t				max;

	vec3_t				bbmin;			// clipping bounding box
	vec3_t				bbmax;

	int					flags;

	int					numbones;			// bones
	int					boneindex;

	int					numbonecontrollers;		// bone controllers
	int					bonecontrollerindex;

	int					numhitboxes;			// complex bounding boxes
	int					hitboxindex;

	int					numseq;				// animation sequences
	int					seqindex;

	int					numseqgroups;		// demand loaded sequences
	int					seqgroupindex;

	int					numtextures;		// raw textures
	int					textureindex;
	int					texturedataindex;

	int					numskinref;			// replaceable textures
	int					numskinfamilies;
	int					skinindex;

	int					numbodyparts;
	int					bodypartindex;

	int					numattachments;		// queryable attachable points
	int					attachmentindex;

	int					soundtable;
	int					soundindex;
	int					soundgroups;
	int					soundgroupindex;

	int					numtransitions;		// animation node to animation node transition graph
	int					transitionindex;
} studiohdr_t;

// header for demand loaded sequence group data
typedef struct
{
	int					id;
	int					version;

	char				name[64];
	int					length;
} studioseqhdr_t;

// bones
typedef struct
{
	char				name[32];	// bone name for symbolic links
	int		 			parent;		// parent bone
	int					flags;		// ??
	int					bonecontroller[6];	// bone controller index, -1 == none
	float				value[6];	// default DoF values
	float				scale[6];   // scale for delta DoF values
} mstudiobone_t;


// bone controllers
typedef struct
{
	int					bone;	// -1 == 0
	int					type;	// X, Y, Z, XR, YR, ZR, M
	float				start;
	float				end;
	int					rest;	// byte index value at rest
	int					index;	// 0-3 user set controller, 4 mouth
} mstudiobonecontroller_t;

// intersection boxes
typedef struct
{
	int					bone;
	int					group;			// intersection group
	vec3_t				bbmin;		// bounding box
	vec3_t				bbmax;
} mstudiobbox_t;

#if !defined( CACHE_USER ) && !defined( QUAKEDEF_H )
#define CACHE_USER
typedef struct cache_user_s
{
	void* data;
} cache_user_t;
#endif

//
// demand loaded sequence groups
//
typedef struct
{
	char				label[32];	// textual name
	char				name[64];	// file name
	int					unused1;    // was "cache"  - index pointer
	int					unused2;    // was "data" -  hack for group 0
} mstudioseqgroup_t;

// sequence descriptions
typedef struct
{
	char				label[32];	// sequence label

	float				fps;		// frames per second	
	int					flags;		// looping/non-looping flags

	int					activity;
	int					actweight;

	int					numevents;
	int					eventindex;

	int					numframes;	// number of frames per sequence

	int					numpivots;	// number of foot pivots
	int					pivotindex;

	int					motiontype;
	int					motionbone;
	vec3_t				linearmovement;
	int					automoveposindex;
	int					automoveangleindex;

	vec3_t				bbmin;		// per sequence bounding box
	vec3_t				bbmax;

	int					numblends;
	int					animindex;		// mstudioanim_t pointer relative to start of sequence group data
										// [blend][bone][X, Y, Z, XR, YR, ZR]

	int					blendtype[2];	// X, Y, Z, XR, YR, ZR
	float				blendstart[2];	// starting value
	float				blendend[2];	// ending value
	int					blendparent;

	int					seqgroup;		// sequence group for demand loading

	int					entrynode;		// transition node at entry
	int					exitnode;		// transition node at exit
	int					nodeflags;		// transition rules

	int					nextseq;		// auto advancing sequences
} mstudioseqdesc_t;

// events
typedef struct
{
	int 				frame;
	int					event;
	int					type;
	char				options[64];
} mstudioevent_t;

// pivots
typedef struct
{
	vec3_t				org;	// pivot point
	int					start;
	int					end;
} mstudiopivot_t;

// attachment
typedef struct
{
	char				name[32];
	int					type;
	int					bone;
	vec3_t				org;	// attachment point
	vec3_t				vectors[3];
} mstudioattachment_t;

typedef struct
{
	unsigned short	offset[6];
} mstudioanim_t;

// animation frames
typedef union
{
	struct {
		byte	valid;
		byte	total;
	} num;
	short		value;
} mstudioanimvalue_t;



// body part index
typedef struct
{
	char				name[64];
	int					nummodels;
	int					base;
	int					modelindex; // index into models array
} mstudiobodyparts_t;



// skin info
typedef struct
{
	char					name[64];
	int						flags;
	int						width;
	int						height;
	int						index;
} mstudiotexture_t;


// skin families
// short	index[skinfamilies][skinref]

// studio models
typedef struct
{
	char				name[64];

	int					type;

	float				boundingradius;

	int					nummesh;
	int					meshindex;

	int					numverts;		// number of unique vertices
	int					vertinfoindex;	// vertex bone info
	int					vertindex;		// vertex vec3_t
	int					numnorms;		// number of unique surface normals
	int					norminfoindex;	// normal bone info
	int					normindex;		// normal vec3_t

	int					numgroups;		// deformation groups
	int					groupindex;
} mstudiomodel_t;


// vec3_t	boundingbox[model][bone][2];	// complex intersection info


// meshes
typedef struct
{
	int					numtris;
	int					triindex;
	int					skinref;
	int					numnorms;		// per mesh normals
	int					normindex;		// normal vec3_t
} mstudiomesh_t;

// triangles
#if 0
typedef struct
{
	short				vertindex;		// index into vertex array
	short				normindex;		// index into normal array
	short				s, t;			// s,t position on skin
} mstudiotrivert_t;
#endif

// lighting options
#define STUDIO_NF_FLATSHADE		0x0001
#define STUDIO_NF_CHROME		0x0002
#define STUDIO_NF_FULLBRIGHT	0x0004
#define STUDIO_NF_NOMIPS        0x0008
#define STUDIO_NF_ALPHA         0x0010
#define STUDIO_NF_ADDITIVE      0x0020
#define STUDIO_NF_MASKED        0x0040

// motion flags
#define STUDIO_X		0x0001
#define STUDIO_Y		0x0002	
#define STUDIO_Z		0x0004
#define STUDIO_XR		0x0008
#define STUDIO_YR		0x0010
#define STUDIO_ZR		0x0020
#define STUDIO_LX		0x0040
#define STUDIO_LY		0x0080
#define STUDIO_LZ		0x0100
#define STUDIO_AX		0x0200
#define STUDIO_AY		0x0400
#define STUDIO_AZ		0x0800
#define STUDIO_AXR		0x1000
#define STUDIO_AYR		0x2000
#define STUDIO_AZR		0x4000
#define STUDIO_TYPES	0x7FFF
#define STUDIO_RLOOP	0x8000	// controller that wraps shortest distance

// sequence flags
#define STUDIO_LOOPING	0x0001

// bone flags
#define STUDIO_HAS_NORMALS	0x0001
#define STUDIO_HAS_VERTICES 0x0002
#define STUDIO_HAS_BBOX		0x0004
#define STUDIO_HAS_CHROME	0x0008	// if any of the textures have chrome on them

#define RAD_TO_STUDIO		(32768.0/M_PI)
#define STUDIO_TO_RAD		(M_PI/32768.0)

#define STUDIO_INTERFACE_VERSION 1

typedef struct engine_studio_api_s
{
	// Allocate number*size bytes and zero it
	void* (*Mem_Calloc)				(int number, size_t size);
	// Check to see if pointer is in the cache
	void* (*Cache_Check)				(struct cache_user_s* c);
	// Load file into cache ( can be swapped out on demand )
	void			(*LoadCacheFile)				(char* path, struct cache_user_s* cu);
	// Retrieve model pointer for the named model
	struct model_s* (*Mod_ForName)				(const char* name, int crash_if_missing);
	// Retrieve pointer to studio model data block from a model
	void* (*Mod_Extradata)				(struct model_s* mod);
	// Retrieve indexed model from client side model precache list
	struct model_s* (*GetModelByIndex)			(int index);
	// Get entity that is set for rendering
	struct cl_entity_s* (*GetCurrentEntity)		(void);
	// Get referenced player_info_t
	struct player_info_s* (*PlayerInfo)			(int index);
	// Get most recently received player state data from network system
	struct entity_state_s* (*GetPlayerState)		(int index);
	// Get viewentity
	struct cl_entity_s* (*GetViewEntity)			(void);
	// Get current frame count, and last two timestampes on client
	void			(*GetTimes)					(int* framecount, double* current, double* old);
	// Get a pointer to a cvar by name
	struct cvar_s* (*GetCvar)					(const char* name);
	// Get current render origin and view vectors ( up, right and vpn )
	void			(*GetViewInfo)				(float* origin, float* upv, float* rightv, float* vpnv);
	// Get sprite model used for applying chrome effect
	struct model_s* (*GetChromeSprite)			(void);
	// Get model counters so we can incement instrumentation
	void			(*GetModelCounters)			(int** s, int** a);
	// Get software scaling coefficients
	void			(*GetAliasScale)				(float* x, float* y);

	// Get bone, light, alias, and rotation matrices
	float**** (*StudioGetBoneTransform) (void);
	float**** (*StudioGetLightTransform)(void);
	float*** (*StudioGetAliasTransform) (void);
	float*** (*StudioGetRotationMatrix) (void);

	// Set up body part, and get submodel pointers
	void			(*StudioSetupModel)			(int bodypart, void** ppbodypart, void** ppsubmodel);
	// Check if entity's bbox is in the view frustum
	int				(*StudioCheckBBox)			(void);
	// Apply lighting effects to model
	void			(*StudioDynamicLight)			(struct cl_entity_s* ent, struct alight_s* plight);
	void			(*StudioEntityLight)			(struct alight_s* plight);
	void			(*StudioSetupLighting)		(struct alight_s* plighting);

	// Draw mesh vertices
	void			(*StudioDrawPoints)			(void);

	// Draw hulls around bones
	void			(*StudioDrawHulls)			(void);
	// Draw bbox around studio models
	void			(*StudioDrawAbsBBox)			(void);
	// Draws bones
	void			(*StudioDrawBones)			(void);
	// Loads in appropriate texture for model
	void			(*StudioSetupSkin)			(void* ptexturehdr, int index);
	// Sets up for remapped colors
	void			(*StudioSetRemapColors)		(int top, int bottom);
	// Set's player model and returns model pointer
	struct model_s* (*SetupPlayerModel)			(int index);
	// Fires any events embedded in animation
	void			(*StudioClientEvents)			(void);
	// Retrieve/set forced render effects flags
	int				(*GetForceFaceFlags)			(void);
	void			(*SetForceFaceFlags)			(int flags);
	// Tell engine the value of the studio model header
	void			(*StudioSetHeader)			(void* header);
	// Tell engine which model_t * is being renderered
	void			(*SetRenderModel)				(struct model_s* model);

	// Final state setup and restore for rendering
	void			(*SetupRenderer)				(int rendermode);
	void			(*RestoreRenderer)			(void);

	// Set render origin for applying chrome effect
	void			(*SetChromeOrigin)			(void);

	// True if using D3D/OpenGL
	int				(*IsHardware)					(void);

	// Only called by hardware interface
	void			(*GL_StudioDrawShadow)		(void);
	void			(*GL_SetRenderMode)			(int mode);

	void			(*StudioSetRenderamt)			(int iRenderamt); 	//!!!CZERO added for rendering glass on viewmodels
	void			(*StudioSetCullState)			(int iCull);
	void			(*StudioRenderShadow)			(int iSprite, float* p1, float* p2, float* p3, float* p4);
} engine_studio_api_t;

typedef struct server_studio_api_s
{
	// Allocate number*size bytes and zero it
	void* (*Mem_Calloc)				(int number, size_t size);
	// Check to see if pointer is in the cache
	void* (*Cache_Check)				(struct cache_user_s* c);
	// Load file into cache ( can be swapped out on demand )
	void			(*LoadCacheFile)				(char* path, struct cache_user_s* cu);
	// Retrieve pointer to studio model data block from a model
	void* (*Mod_Extradata)				(struct model_s* mod);
} server_studio_api_t;


// client blending
typedef struct r_studio_interface_s
{
	int				version;
	int				(*StudioDrawModel)			(int flags);
	int				(*StudioDrawPlayer)			(int flags, struct entity_state_s* pplayer);
} r_studio_interface_t;

extern r_studio_interface_t* pStudioAPI;

// server blending
#define SV_BLENDING_INTERFACE_VERSION 1

typedef struct sv_blending_interface_s
{
	int				version;

	void			(*SV_StudioSetupBones)		(struct model_s* pModel,
		float				frame,
		int				sequence,
		const vec3_t		angles,
		const	vec3_t		origin,
		const	byte* pcontroller,
		const	byte* pblending,
		int				iBone,
		const edict_t* pEdict);
} sv_blending_interface_t;

#define STUDIO_RENDER 1
#define STUDIO_EVENTS 2

#define MAX_CLIENTS			32
#define	MAX_EDICTS			900

#define MAX_MODEL_NAME		64
#define MAX_MAP_HULLS		4
#define	MIPLEVELS			4
#define	NUM_AMBIENTS		4		// automatic ambient sounds
#define	MAXLIGHTMAPS		4
#define	PLANE_ANYZ			5

#define ALIAS_Z_CLIP_PLANE	5

// flags in finalvert_t.flags
#define ALIAS_LEFT_CLIP				0x0001
#define ALIAS_TOP_CLIP				0x0002
#define ALIAS_RIGHT_CLIP			0x0004
#define ALIAS_BOTTOM_CLIP			0x0008
#define ALIAS_Z_CLIP				0x0010
#define ALIAS_ONSEAM				0x0020
#define ALIAS_XY_CLIP_MASK			0x000F

#define	ZISCALE	((float)0x8000)

#define CACHE_SIZE	32		// used to align key data structures

typedef enum
{
	mod_brush,
	mod_sprite,
	mod_alias,
	mod_studio
} modtype_t;

// must match definition in modelgen.h
#ifndef SYNCTYPE_T
#define SYNCTYPE_T

typedef enum
{
	ST_SYNC = 0,
	ST_RAND
} synctype_t;

#endif

typedef struct texture_s texture_t;

typedef struct
{
	float		mins[3], maxs[3];
	float		origin[3];
	int			headnode[MAX_MAP_HULLS];
	int			visleafs;		// not including the solid leaf 0
	int			firstface, numfaces;
} dmodel_t;

// plane_t structure
typedef struct mplane_s
{
	vec3_t	normal;			// surface normal
	float	dist;			// closest appoach to origin
	byte	type;			// for texture axis selection and fast side tests
	byte	signbits;		// signx + signy<<1 + signz<<1
	byte	pad[2];
} mplane_t;

typedef struct
{
	vec3_t		position;
} mvertex_t;

typedef struct
{
	unsigned short	v[2];
	unsigned int	cachededgeoffset;
} medge_t;

typedef struct
{
	float		vecs[2][4];		// [s/t] unit vectors in world space. 
	// [i][3] is the s/t offset relative to the origin.
	// s or t = dot(3Dpoint,vecs[i])+vecs[i][3]
	float		mipadjust;		// ?? mipmap limits for very small surfaces
	texture_t* texture;
	int			flags;			// sky or slime, no lightmap or 256 subdivision
} mtexinfo_t;

typedef struct mnode_s
{
	// common with leaf
	int			contents;		// 0, to differentiate from leafs
	int			visframe;		// node needs to be traversed if current

	short		minmaxs[6];		// for bounding box culling

	struct mnode_s* parent;

	// node specific
	mplane_t* plane;
	struct mnode_s* children[2];

	unsigned short		firstsurface;
	unsigned short		numsurfaces;
} mnode_t;

typedef struct msurface_s	msurface_t;
typedef struct decal_s		decal_t;

// JAY: Compress this as much as possible
struct decal_s
{
	decal_t* pnext;			// linked list for each surface
	msurface_t* psurface;		// Surface id for persistence / unlinking
	short		dx;				// Offsets into surface texture (in texture coordinates, so we don't need floats)
	short		dy;
	short		texture;		// Decal texture
	byte		scale;			// Pixel scale
	byte		flags;			// Decal flags

	short		entityIndex;	// Entity this is attached to
};

typedef struct mleaf_s
{
	// common with node
	int			contents;		// wil be a negative contents number
	int			visframe;		// node needs to be traversed if current

	short		minmaxs[6];		// for bounding box culling

	struct mnode_s* parent;

	// leaf specific
	byte* compressed_vis;
	struct efrag_s* efrags;

	msurface_t** firstmarksurface;
	int			nummarksurfaces;
	int			key;			// BSP sequence number for leaf's contents
	byte		ambient_sound_level[NUM_AMBIENTS];
} mleaf_t;

struct msurface_s
{
	int			visframe;		// should be drawn when node is crossed

	int			dlightframe;	// last frame the surface was checked by an animated light
	int			dlightbits;		// dynamically generated. Indicates if the surface illumination 
	// is modified by an animated light.

	mplane_t* plane;			// pointer to shared plane			
	int			flags;			// see SURF_ #defines

	int			firstedge;	// look up in model->surfedges[], negative numbers
	int			numedges;	// are backwards edges

	// surface generation data
	struct surfcache_s* cachespots[MIPLEVELS];

	short		texturemins[2]; // smallest s/t position on the surface.
	short		extents[2];		// ?? s/t texture size, 1..256 for all non-sky surfaces

	mtexinfo_t* texinfo;

	// lighting info
	byte		styles[MAXLIGHTMAPS]; // index into d_lightstylevalue[] for animated lights 
	// no one surface can be effected by more than 4 
	// animated lights.
	color24* samples;

	decal_t* pdecals;
};

typedef struct mdisplaylist_s
{
	unsigned int gl_displaylist;
	int rendermode;
	float scrolloffset;
	int renderDetailTexture;
} mdisplaylist_t;

typedef struct glpoly_s
{
	glpoly_s* next;
	glpoly_s* chain;
	int numverts;
	int flags;
	float verts[4][7];
} glpoly_t;


typedef struct msurface_HL25_s
{
	int visframe;
	mplane_t* plane;
	int flags;
	int firstedge;
	int numedges;
	__int16 texturemins[2];
	__int16 extents[2];
	int light_s;
	int light_t;
	glpoly_t* polys;
	msurface_s* texturechain;
	mtexinfo_t* texinfo;
	int dlightframe;
	int dlightbits;
	int lightmaptexturenum;
	byte styles[4];
	int cached_light[4];
	qboolean cached_dlight;
	color24* samples;
	decal_t* pdecals;
	mdisplaylist_t displaylist;
} msurface_HL25_t;


typedef struct
{
	int			planenum;
	short		children[2];	// negative numbers are contents
} dclipnode_t;

typedef struct hull_s
{
	dclipnode_t* clipnodes;
	mplane_t* planes;
	int			firstclipnode;
	int			lastclipnode;
	vec3_t		clip_mins;
	vec3_t		clip_maxs;
} hull_t;

#if !defined( CACHE_USER ) && !defined( QUAKEDEF_H )
#define CACHE_USER
typedef struct cache_user_s
{
	void* data;
} cache_user_t;
#endif

typedef struct model_s
{
	char		name[MAX_MODEL_NAME];
	qboolean	needload;		// bmodels and sprites don't cache normally

	modtype_t	type;
	int			numframes;
	synctype_t	synctype;

	int			flags;

	//
	// volume occupied by the model
	//		
	vec3_t		mins, maxs;
	float		radius;

	//
	// brush model
	//
	int			firstmodelsurface, nummodelsurfaces;

	int			numsubmodels;
	dmodel_t* submodels;

	int			numplanes;
	mplane_t* planes;

	int			numleafs;		// number of visible leafs, not counting 0
	struct mleaf_s* leafs;

	int			numvertexes;
	mvertex_t* vertexes;

	int			numedges;
	medge_t* edges;

	int			numnodes;
	mnode_t* nodes;

	int			numtexinfo;
	mtexinfo_t* texinfo;

	int			numsurfaces;
	msurface_t* surfaces;

	int			numsurfedges;
	int* surfedges;

	int			numclipnodes;
	dclipnode_t* clipnodes;

	int			nummarksurfaces;
	msurface_t** marksurfaces;

	hull_t		hulls[MAX_MAP_HULLS];

	int			numtextures;
	texture_t** textures;

	byte* visdata;

	color24* lightdata;

	char* entities;

	//
	// additional model data
	//
	cache_user_t	cache;		// only access through Mod_Extradata

} model_t;

typedef struct model_HL25_s
{
	char		name[MAX_MODEL_NAME];
	qboolean	needload;		// bmodels and sprites don't cache normally

	modtype_t	type;
	int			numframes;
	synctype_t	synctype;

	int			flags;

	//
	// volume occupied by the model
	//		
	vec3_t		mins, maxs;
	float		radius;

	//
	// brush model
	//
	int			firstmodelsurface, nummodelsurfaces;

	int			numsubmodels;
	dmodel_t* submodels;

	int			numplanes;
	mplane_t* planes;

	int			numleafs;		// number of visible leafs, not counting 0
	struct mleaf_s* leafs;

	int			numvertexes;
	mvertex_t* vertexes;

	int			numedges;
	medge_t* edges;

	int			numnodes;
	mnode_t* nodes;

	int			numtexinfo;
	mtexinfo_t* texinfo;

	int			numsurfaces;
	msurface_HL25_t* surfaces;

	int			numsurfedges;
	int* surfedges;

	int			numclipnodes;
	dclipnode_t* clipnodes;

	int			nummarksurfaces;
	msurface_HL25_t** marksurfaces;

	hull_t		hulls[MAX_MAP_HULLS];

	int			numtextures;
	texture_t** textures;

	byte* visdata;

	color24* lightdata;

	char* entities;

	//
	// additional model data
	//
	cache_user_t	cache;		// only access through Mod_Extradata

} model_HL25_t;


#define EVENT_API_VERSION 1

typedef struct event_api_s
{
	int		version;
	void	(*EV_PlaySound) (int ent, float* origin, int channel, const char* sample, float volume, float attenuation, int fFlags, int pitch);
	void	(*EV_StopSound) (int ent, int channel, const char* sample);
	int		(*EV_FindModelIndex)(const char* pmodel);
	int		(*EV_IsLocal) (int playernum);
	int		(*EV_LocalPlayerDucking) (void);
	void	(*EV_LocalPlayerViewheight) (float*);
	void	(*EV_LocalPlayerBounds) (int hull, float* mins, float* maxs);
	int		(*EV_IndexFromTrace) (struct pmtrace_s* pTrace);
	struct physent_s* (*EV_GetPhysent) (int idx);
	void	(*EV_SetUpPlayerPrediction) (int dopred, int bIncludeLocalClient);
	void	(*EV_PushPMStates) (void);
	void	(*EV_PopPMStates) (void);
	void	(*EV_SetSolidPlayers) (int playernum);
	void	(*EV_SetTraceHull) (int hull);
	void	(*EV_PlayerTrace) (float* start, float* end, int traceFlags, int ignore_pe, struct pmtrace_s* tr);
	void	(*EV_WeaponAnimation) (int sequence, int body);
	unsigned short (*EV_PrecacheEvent) (int type, const char* psz);
	void	(*EV_PlaybackEvent) (int flags, const struct edict_s* pInvoker, unsigned short eventindex, float delay, float* origin, float* angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);
	const char* (*EV_TraceTexture) (int ground, float* vstart, float* vend);
	void	(*EV_StopAllSounds) (int entnum, int entchannel);
	void    (*EV_KillEvents) (int entnum, const char* eventname);
} event_api_t;

typedef enum
{
	TRI_FRONT = 0,
	TRI_NONE = 1,
} TRICULLSTYLE;

#define TRI_API_VERSION		1

#define TRI_TRIANGLES		0
#define TRI_TRIANGLE_FAN	1
#define TRI_QUADS			2
#define TRI_POLYGON			3
#define TRI_LINES			4	
#define TRI_TRIANGLE_STRIP	5
#define TRI_QUAD_STRIP		6

typedef struct triangleapi_s
{
	int			version;

	void		(*RenderMode)(int mode);
	void		(*Begin)(int primitiveCode);
	void		(*End) (void);

	void		(*Color4f) (float r, float g, float b, float a);
	void		(*Color4ub) (unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void		(*TexCoord2f) (float u, float v);
	void		(*Vertex3fv) (float* worldPnt);
	void		(*Vertex3f) (float x, float y, float z);
	void		(*Brightness) (float brightness);
	void		(*CullFace) (TRICULLSTYLE style);
	int			(*SpriteTexture) (struct model_s* pSpriteModel, int frame);
	int			(*WorldToScreen) (float* world, float* screen);  // Returns 1 if it's z clipped
	void		(*Fog) (float flFogColor[3], float flStart, float flEnd, int bOn); // Works just like GL_FOG, flFogColor is r/g/b.
	void		(*ScreenToWorld) (float* screen, float* world);
	void		(*GetMatrix) (const int pname, float* matrix);
	int			(*BoxInPVS) (float* mins, float* maxs);
	void		(*LightAtPoint) (float* pos, float* value);
	void		(*Color4fRendermode) (float r, float g, float b, float a, int rendermode);
	void		(*FogParams) (float flDensity, int iFogSkybox); // Used with Fog()...sets fog density and whether the fog should be applied to the skybox

} triangleapi_t;

// Temporary entity array
#define TENTPRIORITY_LOW	0
#define TENTPRIORITY_HIGH	1

// TEMPENTITY flags
#define	FTENT_NONE				0x00000000
#define	FTENT_SINEWAVE			0x00000001
#define	FTENT_GRAVITY			0x00000002
#define FTENT_ROTATE			0x00000004
#define	FTENT_SLOWGRAVITY		0x00000008
#define FTENT_SMOKETRAIL		0x00000010
#define FTENT_COLLIDEWORLD		0x00000020
#define FTENT_FLICKER			0x00000040
#define FTENT_FADEOUT			0x00000080
#define FTENT_SPRANIMATE		0x00000100
#define FTENT_HITSOUND			0x00000200
#define FTENT_SPIRAL			0x00000400
#define FTENT_SPRCYCLE			0x00000800
#define FTENT_COLLIDEALL		0x00001000 // will collide with world and slideboxes
#define FTENT_PERSIST			0x00002000 // tent is not removed when unable to draw 
#define FTENT_COLLIDEKILL		0x00004000 // tent is removed upon collision with anything
#define FTENT_PLYRATTACHMENT	0x00008000 // tent is attached to a player (owner)
#define FTENT_SPRANIMATELOOP	0x00010000 // animating sprite doesn't die when last frame is displayed
#define FTENT_SPARKSHOWER		0x00020000
#define FTENT_NOMODEL			0x00040000 // Doesn't have a model, never try to draw ( it just triggers other things )
#define FTENT_CLIENTCUSTOM		0x00080000 // Must specify callback.  Callback function is responsible for killing tempent and updating fields ( unless other flags specify how to do things )

typedef struct tempent_s
{
	int			flags;
	float		die;
	float		frameMax;
	float		x;
	float		y;
	float		z;
	float		fadeSpeed;
	float		bounceFactor;
	int			hitSound;
	void		(*hitcallback)	(struct tempent_s* ent, struct pmtrace_s* ptr);
	void		(*callback)		(struct tempent_s* ent, float frametime, float currenttime);
	struct tempent_s* next;
	int			priority;
	short		clientIndex;	// if attached, this is the index of the client to stick to
	// if COLLIDEALL, this is the index of the client to ignore
	// TENTS with FTENT_PLYRATTACHMENT MUST set the clientindex! 

	vec3_t		tentOffset;		// if attached, client origin + tentOffset = tent origin.
	cl_entity_t	entity;

	// baseline.origin		- velocity
	// baseline.renderamt	- starting fadeout intensity
	// baseline.angles		- angle velocity
} TEMPENTITY;

#define FBEAM_STARTENTITY		0x00000001
#define FBEAM_ENDENTITY			0x00000002
#define FBEAM_FADEIN			0x00000004
#define FBEAM_FADEOUT			0x00000008
#define FBEAM_SINENOISE			0x00000010
#define FBEAM_SOLID				0x00000020
#define FBEAM_SHADEIN			0x00000040
#define FBEAM_SHADEOUT			0x00000080
#define FBEAM_STARTVISIBLE		0x10000000		// Has this client actually seen this beam's start entity yet?
#define FBEAM_ENDVISIBLE		0x20000000		// Has this client actually seen this beam's end entity yet?
#define FBEAM_ISACTIVE			0x40000000
#define FBEAM_FOREVER			0x80000000

typedef enum {
	pt_static,
	pt_grav,
	pt_slowgrav,
	pt_fire,
	pt_explode,
	pt_explode2,
	pt_blob,
	pt_blob2,
	pt_vox_slowgrav,
	pt_vox_grav,
	pt_clientcustom   // Must have callback function specified
} ptype_t;

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
typedef struct particle_s
{
	// driver-usable fields
	vec3_t		org;
	short		color;
	short		packedColor;
	// drivers never touch the following fields
	struct particle_s* next;
	vec3_t		vel;
	float		ramp;
	float		die;
	ptype_t		type;
	void		(*deathfunc)(struct particle_s* particle);

	// for pt_clientcusttom, we'll call this function each frame
	void		(*callback)(struct particle_s* particle, float frametime);

	// For deathfunc, etc.
	unsigned char context;
} particle_t;

typedef struct beam_s BEAM;
struct beam_s
{
	BEAM* next;
	int			type;
	int			flags;
	vec3_t		source;
	vec3_t		target;
	vec3_t		delta;
	float		t;		// 0 .. 1 over lifetime of beam
	float		freq;
	float		die;
	float		width;
	float		amplitude;
	float		r, g, b;
	float		brightness;
	float		speed;
	float		frameRate;
	float		frame;
	int			segments;
	int			startEntity;
	int			endEntity;
	int			modelIndex;
	int			frameCount;
	struct model_s* pFollowModel;
	struct particle_s* particles;
};

typedef struct dlight_s dlight_t;

typedef struct efx_api_s efx_api_t;

struct efx_api_s
{
	particle_t* (*R_AllocParticle)			(void (*callback) (struct particle_s* particle, float frametime));
	void		(*R_BlobExplosion)			(float* org);
	void		(*R_Blood)					(float* org, float* dir, int pcolor, int speed);
	void		(*R_BloodSprite)				(float* org, int colorindex, int modelIndex, int modelIndex2, float size);
	void		(*R_BloodStream)				(float* org, float* dir, int pcolor, int speed);
	void		(*R_BreakModel)				(float* pos, float* size, float* dir, float random, float life, int count, int modelIndex, char flags);
	void		(*R_Bubbles)					(float* mins, float* maxs, float height, int modelIndex, int count, float speed);
	void		(*R_BubbleTrail)				(float* start, float* end, float height, int modelIndex, int count, float speed);
	void		(*R_BulletImpactParticles)	(float* pos);
	void		(*R_EntityParticles)			(struct cl_entity_s* ent);
	void		(*R_Explosion)				(float* pos, int model, float scale, float framerate, int flags);
	void		(*R_FizzEffect)				(struct cl_entity_s* pent, int modelIndex, int density);
	void		(*R_FireField) 				(float* org, int radius, int modelIndex, int count, int flags, float life);
	void		(*R_FlickerParticles)			(float* org);
	void		(*R_FunnelSprite)				(float* org, int modelIndex, int reverse);
	void		(*R_Implosion)				(float* end, float radius, int count, float life);
	void		(*R_LargeFunnel)				(float* org, int reverse);
	void		(*R_LavaSplash)				(float* org);
	void		(*R_MultiGunshot)				(float* org, float* dir, float* noise, int count, int decalCount, int* decalIndices);
	void		(*R_MuzzleFlash)				(float* pos1, int type);
	void		(*R_ParticleBox)				(float* mins, float* maxs, unsigned char r, unsigned char g, unsigned char b, float life);
	void		(*R_ParticleBurst)			(float* pos, int size, int color, float life);
	void		(*R_ParticleExplosion)		(float* org);
	void		(*R_ParticleExplosion2)		(float* org, int colorStart, int colorLength);
	void		(*R_ParticleLine)				(float* start, float* end, unsigned char r, unsigned char g, unsigned char b, float life);
	void		(*R_PlayerSprites)			(int client, int modelIndex, int count, int size);
	void		(*R_Projectile)				(float* origin, float* velocity, int modelIndex, int life, int owner, void (*hitcallback)(struct tempent_s* ent, struct pmtrace_s* ptr));
	void		(*R_RicochetSound)			(float* pos);
	void		(*R_RicochetSprite)			(float* pos, struct model_s* pmodel, float duration, float scale);
	void		(*R_RocketFlare)				(float* pos);
	void		(*R_RocketTrail)				(float* start, float* end, int type);
	void		(*R_RunParticleEffect)		(float* org, float* dir, int color, int count);
	void		(*R_ShowLine)					(float* start, float* end);
	void		(*R_SparkEffect)				(float* pos, int count, int velocityMin, int velocityMax);
	void		(*R_SparkShower)				(float* pos);
	void		(*R_SparkStreaks)				(float* pos, int count, int velocityMin, int velocityMax);
	void		(*R_Spray)					(float* pos, float* dir, int modelIndex, int count, int speed, int spread, int rendermode);
	void		(*R_Sprite_Explode)			(TEMPENTITY* pTemp, float scale, int flags);
	void		(*R_Sprite_Smoke)				(TEMPENTITY* pTemp, float scale);
	void		(*R_Sprite_Spray)				(float* pos, float* dir, int modelIndex, int count, int speed, int iRand);
	void		(*R_Sprite_Trail)				(int type, float* start, float* end, int modelIndex, int count, float life, float size, float amplitude, int renderamt, float speed);
	void		(*R_Sprite_WallPuff)			(TEMPENTITY* pTemp, float scale);
	void		(*R_StreakSplash)				(float* pos, float* dir, int color, int count, float speed, int velocityMin, int velocityMax);
	void		(*R_TracerEffect)				(float* start, float* end);
	void		(*R_UserTracerParticle)		(float* org, float* vel, float life, int colorIndex, float length, unsigned char deathcontext, void (*deathfunc)(struct particle_s* particle));
	particle_t* (*R_TracerParticles)			(float* org, float* vel, float life);
	void		(*R_TeleportSplash)			(float* org);
	void		(*R_TempSphereModel)			(float* pos, float speed, float life, int count, int modelIndex);
	TEMPENTITY* (*R_TempModel)				(float* pos, float* dir, float* angles, float life, int modelIndex, int soundtype);
	TEMPENTITY* (*R_DefaultSprite)			(float* pos, int spriteIndex, float framerate);
	TEMPENTITY* (*R_TempSprite)				(float* pos, float* dir, float scale, int modelIndex, int rendermode, int renderfx, float a, float life, int flags);
	int			(*Draw_DecalIndex)			(int id);
	int			(*Draw_DecalIndexFromName)	(char* name);
	void		(*R_DecalShoot)				(int textureIndex, int entity, int modelIndex, float* position, int flags);
	void		(*R_AttachTentToPlayer)		(int client, int modelIndex, float zoffset, float life);
	void		(*R_KillAttachedTents)		(int client);
	BEAM* (*R_BeamCirclePoints)		(int type, float* start, float* end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	BEAM* (*R_BeamEntPoint)			(int startEnt, float* end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	BEAM* (*R_BeamEnts)				(int startEnt, int endEnt, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	BEAM* (*R_BeamFollow)				(int startEnt, int modelIndex, float life, float width, float r, float g, float b, float brightness);
	void		(*R_BeamKill)					(int deadEntity);
	BEAM* (*R_BeamLightning)			(float* start, float* end, int modelIndex, float life, float width, float amplitude, float brightness, float speed);
	BEAM* (*R_BeamPoints)				(float* start, float* end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	BEAM* (*R_BeamRing)				(int startEnt, int endEnt, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	dlight_t* (*CL_AllocDlight)			(int key);
	dlight_t* (*CL_AllocElight)			(int key);
	TEMPENTITY* (*CL_TempEntAlloc)			(float* org, struct model_s* model);
	TEMPENTITY* (*CL_TempEntAllocNoModel)	(float* org);
	TEMPENTITY* (*CL_TempEntAllocHigh)		(float* org, struct model_s* model);
	TEMPENTITY* (*CL_TentEntAllocCustom)		(float* origin, struct model_s* model, int high, void (*callback) (struct tempent_s* ent, float frametime, float currenttime));
	void		(*R_GetPackedColor)			(short* packed, short color);
	short		(*R_LookupColor)				(unsigned char r, unsigned char g, unsigned char b);
	void		(*R_DecalRemoveAll)			(int textureIndex); //textureIndex points to the decal index in the array, not the actual texture index.
	void		(*R_FireCustomDecal)			(int textureIndex, int entity, int modelIndex, float* position, int flags, float scale);
};
// ********************************************************
// Functions exported by the engine
// ********************************************************

// Function type declarations for engine exports
typedef HSPRITE_HL					(*pfnEngSrc_pfnSPR_Load_t)			(const char* szPicName);
typedef int							(*pfnEngSrc_pfnSPR_Frames_t)			(HSPRITE_HL hPic);
typedef int							(*pfnEngSrc_pfnSPR_Height_t)			(HSPRITE_HL hPic, int frame);
typedef int							(*pfnEngSrc_pfnSPR_Width_t)			(HSPRITE_HL hPic, int frame);
typedef void						(*pfnEngSrc_pfnSPR_Set_t)				(HSPRITE_HL hPic, int r, int g, int b);
typedef void						(*pfnEngSrc_pfnSPR_Draw_t)			(int frame, int x, int y, const struct rect_s* prc);
typedef void						(*pfnEngSrc_pfnSPR_DrawHoles_t)		(int frame, int x, int y, const struct rect_s* prc);
typedef void						(*pfnEngSrc_pfnSPR_DrawAdditive_t)	(int frame, int x, int y, const struct rect_s* prc);
typedef void						(*pfnEngSrc_pfnSPR_EnableScissor_t)	(int x, int y, int width, int height);
typedef void						(*pfnEngSrc_pfnSPR_DisableScissor_t)	(void);
typedef struct client_sprite_s* (*pfnEngSrc_pfnSPR_GetList_t)			(char* psz, int* piCount);
typedef void						(*pfnEngSrc_pfnFillRGBA_t)			(int x, int y, int width, int height, int r, int g, int b, int a);
typedef int							(*pfnEngSrc_pfnGetScreenInfo_t) 		(struct SCREENINFO_s* pscrinfo);
typedef void						(*pfnEngSrc_pfnSetCrosshair_t)		(HSPRITE_HL hspr, wrect_t rc, int r, int g, int b);
typedef struct cvar_s* (*pfnEngSrc_pfnRegisterVariable_t)	(char* szName, char* szValue, int flags);
typedef float						(*pfnEngSrc_pfnGetCvarFloat_t)		(char* szName);
typedef char* (*pfnEngSrc_pfnGetCvarString_t)		(char* szName);
typedef int							(*pfnEngSrc_pfnAddCommand_t)			(char* cmd_name, void (*pfnEngSrc_function)(void));
typedef int							(*pfnEngSrc_pfnHookUserMsg_t)			(char* szMsgName, pfnUserMsgHook pfn);
typedef int							(*pfnEngSrc_pfnServerCmd_t)			(char* szCmdString);
typedef int							(*pfnEngSrc_pfnClientCmd_t)			(char* szCmdString);
typedef void						(*pfnEngSrc_pfnPrimeMusicStream_t)	(char* szFilename, int looping);
typedef void						(*pfnEngSrc_pfnGetPlayerInfo_t)		(int ent_num, struct hud_player_info_s* pinfo);
typedef void						(*pfnEngSrc_pfnPlaySoundByName_t)		(char* szSound, float volume);
typedef void						(*pfnEngSrc_pfnPlaySoundByNameAtPitch_t)	(char* szSound, float volume, int pitch);
typedef void						(*pfnEngSrc_pfnPlaySoundVoiceByName_t)		(char* szSound, float volume, int pitch);
typedef void						(*pfnEngSrc_pfnPlaySoundByIndex_t)	(int iSound, float volume);
typedef void						(*pfnEngSrc_pfnAngleVectors_t)		(const float* vecAngles, float* forward, float* right, float* up);
typedef struct client_textmessage_s* (*pfnEngSrc_pfnTextMessageGet_t)		(const char* pName);
typedef int							(*pfnEngSrc_pfnDrawCharacter_t)		(int x, int y, int number, int r, int g, int b);
typedef int							(*pfnEngSrc_pfnDrawConsoleString_t)	(int x, int y, char* string);
typedef void						(*pfnEngSrc_pfnDrawSetTextColor_t)	(float r, float g, float b);
typedef void						(*pfnEngSrc_pfnDrawConsoleStringLen_t)(const char* string, int* length, int* height);
typedef void						(*pfnEngSrc_pfnConsolePrint_t)		(const char* string);
typedef void						(*pfnEngSrc_pfnCenterPrint_t)			(const char* string);
typedef int							(*pfnEngSrc_GetWindowCenterX_t)		(void);
typedef int							(*pfnEngSrc_GetWindowCenterY_t)		(void);
typedef void						(*pfnEngSrc_GetViewAngles_t)			(float*);
typedef void						(*pfnEngSrc_SetViewAngles_t)			(float*);
typedef int							(*pfnEngSrc_GetMaxClients_t)			(void);
typedef void						(*pfnEngSrc_Cvar_SetValue_t)			(char* cvar, float value);
typedef int       					(*pfnEngSrc_Cmd_Argc_t)					(void);
typedef char* (*pfnEngSrc_Cmd_Argv_t)				(int arg);
typedef void						(*pfnEngSrc_Con_Printf_t)				(char* fmt, ...);
typedef void						(*pfnEngSrc_Con_DPrintf_t)			(char* fmt, ...);
typedef void						(*pfnEngSrc_Con_NPrintf_t)			(int pos, char* fmt, ...);
typedef void						(*pfnEngSrc_Con_NXPrintf_t)			(struct con_nprint_s* info, char* fmt, ...);
typedef const char* (*pfnEngSrc_PhysInfo_ValueForKey_t)	(const char* key);
typedef const char* (*pfnEngSrc_ServerInfo_ValueForKey_t)(const char* key);
typedef float						(*pfnEngSrc_GetClientMaxspeed_t)		(void);
typedef int							(*pfnEngSrc_CheckParm_t)				(char* parm, char** ppnext);
typedef void						(*pfnEngSrc_Key_Event_t)				(int key, int down);
typedef void						(*pfnEngSrc_GetMousePosition_t)		(int* mx, int* my);
typedef int							(*pfnEngSrc_IsNoClipping_t)			(void);
typedef struct cl_entity_s* (*pfnEngSrc_GetLocalPlayer_t)		(void);
typedef struct cl_entity_s* (*pfnEngSrc_GetViewModel_t)			(void);
typedef struct cl_entity_s* (*pfnEngSrc_GetEntityByIndex_t)		(int idx);
typedef float						(*pfnEngSrc_GetClientTime_t)			(void);
typedef void						(*pfnEngSrc_V_CalcShake_t)			(void);
typedef void						(*pfnEngSrc_V_ApplyShake_t)			(float* origin, float* angles, float factor);
typedef int							(*pfnEngSrc_PM_PointContents_t)		(float* point, int* truecontents);
typedef int							(*pfnEngSrc_PM_WaterEntity_t)			(float* p);
typedef struct pmtrace_s* (*pfnEngSrc_PM_TraceLine_t)			(float* start, float* end, int flags, int usehull, int ignore_pe);
typedef struct model_s* (*pfnEngSrc_CL_LoadModel_t)			(const char* modelname, int* index);
typedef int							(*pfnEngSrc_CL_CreateVisibleEntity_t)	(int type, struct cl_entity_s* ent);
typedef const struct model_s* (*pfnEngSrc_GetSpritePointer_t)		(HSPRITE_HL HSPRITE_HL);
typedef void						(*pfnEngSrc_pfnPlaySoundByNameAtLocation_t)	(char* szSound, float volume, float* origin);
typedef unsigned short				(*pfnEngSrc_pfnPrecacheEvent_t)		(int type, const char* psz);
typedef void						(*pfnEngSrc_pfnPlaybackEvent_t)		(int flags, const struct edict_s* pInvoker, unsigned short eventindex, float delay, float* origin, float* angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);
typedef void						(*pfnEngSrc_pfnWeaponAnim_t)			(int iAnim, int body);
typedef float						(*pfnEngSrc_pfnRandomFloat_t)			(float flLow, float flHigh);
typedef int32(*pfnEngSrc_pfnRandomLong_t)			(int32 lLow, int32 lHigh);
typedef void						(*pfnEngSrc_pfnHookEvent_t)			(char* name, void (*pfnEvent)(struct event_args_s* args));
typedef int							(*pfnEngSrc_Con_IsVisible_t)			();
typedef const char* (*pfnEngSrc_pfnGetGameDirectory_t)	(void);
typedef struct cvar_s* (*pfnEngSrc_pfnGetCvarPointer_t)		(const char* szName);
typedef const char* (*pfnEngSrc_Key_LookupBinding_t)		(const char* pBinding);
typedef const char* (*pfnEngSrc_pfnGetLevelName_t)		(void);
typedef void						(*pfnEngSrc_pfnGetScreenFade_t)		(struct screenfade_s* fade);
typedef void						(*pfnEngSrc_pfnSetScreenFade_t)		(struct screenfade_s* fade);
typedef void* (*pfnEngSrc_VGui_GetPanel_t)         ();
typedef void                        (*pfnEngSrc_VGui_ViewportPaintBackground_t) (int extents[4]);
typedef byte* (*pfnEngSrc_COM_LoadFile_t)				(char* path, int usehunk, int* pLength);
typedef char* (*pfnEngSrc_COM_ParseFile_t)			(char* data, char* token);
typedef void						(*pfnEngSrc_COM_FreeFile_t)				(void* buffer);
typedef struct triangleapi_s* pTriAPI;
typedef struct efx_api_s* pEfxAPI;
typedef struct event_api_s* pEventAPI;
typedef struct demo_api_s* pDemoAPI;
typedef struct net_api_s* pNetAPI;
typedef struct IVoiceTweak_s* pVoiceTweak;
typedef int							(*pfnEngSrc_IsSpectateOnly_t) (void);
typedef struct model_s* (*pfnEngSrc_LoadMapSprite_t)			(const char* filename);
typedef void						(*pfnEngSrc_COM_AddAppDirectoryToSearchPath_t) (const char* pszBaseDir, const char* appName);
typedef int							(*pfnEngSrc_COM_ExpandFilename_t)				 (const char* fileName, char* nameOutBuffer, int nameOutBufferSize);
typedef const char* (*pfnEngSrc_PlayerInfo_ValueForKey_t)(int playerNum, const char* key);
typedef void						(*pfnEngSrc_PlayerInfo_SetValueForKey_t)(const char* key, const char* value);
typedef qboolean(*pfnEngSrc_GetPlayerUniqueID_t)(int iPlayer, char playerID[16]);
typedef int							(*pfnEngSrc_GetTrackerIDForPlayer_t)(int playerSlot);
typedef int							(*pfnEngSrc_GetPlayerForTrackerID_t)(int trackerID);
typedef int							(*pfnEngSrc_pfnServerCmdUnreliable_t)(char* szCmdString);
typedef void						(*pfnEngSrc_GetMousePos_t)(struct tagPOINT* ppt);
typedef void						(*pfnEngSrc_SetMousePos_t)(int x, int y);
typedef void						(*pfnEngSrc_SetMouseEnable_t)(qboolean fEnable);
typedef struct cvar_s* (*pfnEngSrc_GetFirstCVarPtr_t)();
typedef unsigned int				(*pfnEngSrc_GetFirstCmdFunctionHandle_t)();
typedef unsigned int				(*pfnEngSrc_GetNextCmdFunctionHandle_t)(unsigned int cmdhandle);
typedef const char* (*pfnEngSrc_GetCmdFunctionName_t)(unsigned int cmdhandle);
typedef float						(*pfnEngSrc_GetClientOldTime_t)();
typedef float						(*pfnEngSrc_GetServerGravityValue_t)();
typedef struct model_s* (*pfnEngSrc_GetModelByIndex_t)(int index);
typedef void						(*pfnEngSrc_pfnSetFilterMode_t)(int mode);
typedef void						(*pfnEngSrc_pfnSetFilterColor_t)(float r, float g, float b);
typedef void						(*pfnEngSrc_pfnSetFilterBrightness_t)(float brightness);
typedef sequenceEntry_s* (*pfnEngSrc_pfnSequenceGet_t)(const char* fileName, const char* entryName);
typedef void						(*pfnEngSrc_pfnSPR_DrawGeneric_t)(int frame, int x, int y, const struct rect_s* prc, int src, int dest, int w, int h);
typedef sentenceEntry_s* (*pfnEngSrc_pfnSequencePickSentence_t)(const char* sentenceName, int pickMethod, int* entryPicked);
// draw a complete string
typedef int							(*pfnEngSrc_pfnDrawString_t)		(int x, int y, const char* str, int r, int g, int b);
typedef int							(*pfnEngSrc_pfnDrawStringReverse_t)		(int x, int y, const char* str, int r, int g, int b);
typedef const char* (*pfnEngSrc_LocalPlayerInfo_ValueForKey_t)(const char* key);
typedef int							(*pfnEngSrc_pfnVGUI2DrawCharacter_t)		(int x, int y, int ch, unsigned int font);
typedef int							(*pfnEngSrc_pfnVGUI2DrawCharacterAdd_t)	(int x, int y, int ch, int r, int g, int b, unsigned int font);
typedef unsigned int		(*pfnEngSrc_COM_GetApproxWavePlayLength) (const char* filename);
typedef void* (*pfnEngSrc_pfnGetCareerUI_t)();
typedef void						(*pfnEngSrc_Cvar_Set_t)			(char* cvar, char* value);
typedef int							(*pfnEngSrc_pfnIsPlayingCareerMatch_t)();
typedef double						(*pfnEngSrc_GetAbsoluteTime_t) (void);
typedef void						(*pfnEngSrc_pfnProcessTutorMessageDecayBuffer_t)(int* buffer, int bufferLength);
typedef void						(*pfnEngSrc_pfnConstructTutorMessageDecayBuffer_t)(int* buffer, int bufferLength);
typedef void						(*pfnEngSrc_pfnResetTutorMessageDecayData_t)();
typedef void						(*pfnEngSrc_pfnFillRGBABlend_t)			(int x, int y, int width, int height, int r, int g, int b, int a);
typedef int						(*pfnEngSrc_pfnGetAppID_t)			(void);
typedef cmdalias_t* (*pfnEngSrc_pfnGetAliases_t)		(void);
typedef void					(*pfnEngSrc_pfnVguiWrap2_GetMouseDelta_t) (int* x, int* y);

// Pointers to the exported engine functions themselves
typedef struct cl_enginefuncs_s
{
	pfnEngSrc_pfnSPR_Load_t					pfnSPR_Load;
	pfnEngSrc_pfnSPR_Frames_t				pfnSPR_Frames;
	pfnEngSrc_pfnSPR_Height_t				pfnSPR_Height;
	pfnEngSrc_pfnSPR_Width_t				pfnSPR_Width;
	pfnEngSrc_pfnSPR_Set_t					pfnSPR_Set;
	pfnEngSrc_pfnSPR_Draw_t					pfnSPR_Draw;
	pfnEngSrc_pfnSPR_DrawHoles_t			pfnSPR_DrawHoles;
	pfnEngSrc_pfnSPR_DrawAdditive_t			pfnSPR_DrawAdditive;
	pfnEngSrc_pfnSPR_EnableScissor_t		pfnSPR_EnableScissor;
	pfnEngSrc_pfnSPR_DisableScissor_t		pfnSPR_DisableScissor;
	pfnEngSrc_pfnSPR_GetList_t				pfnSPR_GetList;
	pfnEngSrc_pfnFillRGBA_t					pfnFillRGBA;
	pfnEngSrc_pfnGetScreenInfo_t			pfnGetScreenInfo;
	pfnEngSrc_pfnSetCrosshair_t				pfnSetCrosshair;
	pfnEngSrc_pfnRegisterVariable_t			pfnRegisterVariable;
	pfnEngSrc_pfnGetCvarFloat_t				pfnGetCvarFloat;
	pfnEngSrc_pfnGetCvarString_t			pfnGetCvarString;
	pfnEngSrc_pfnAddCommand_t				pfnAddCommand;
	pfnEngSrc_pfnHookUserMsg_t				pfnHookUserMsg;
	pfnEngSrc_pfnServerCmd_t				pfnServerCmd;
	pfnEngSrc_pfnClientCmd_t				pfnClientCmd;
	pfnEngSrc_pfnGetPlayerInfo_t			pfnGetPlayerInfo;
	pfnEngSrc_pfnPlaySoundByName_t			pfnPlaySoundByName;
	pfnEngSrc_pfnPlaySoundByIndex_t			pfnPlaySoundByIndex;
	pfnEngSrc_pfnAngleVectors_t				pfnAngleVectors;
	pfnEngSrc_pfnTextMessageGet_t			pfnTextMessageGet;
	pfnEngSrc_pfnDrawCharacter_t			pfnDrawCharacter;
	pfnEngSrc_pfnDrawConsoleString_t		pfnDrawConsoleString;
	pfnEngSrc_pfnDrawSetTextColor_t			pfnDrawSetTextColor;
	pfnEngSrc_pfnDrawConsoleStringLen_t		pfnDrawConsoleStringLen;
	pfnEngSrc_pfnConsolePrint_t				pfnConsolePrint;
	pfnEngSrc_pfnCenterPrint_t				pfnCenterPrint;
	pfnEngSrc_GetWindowCenterX_t			GetWindowCenterX;
	pfnEngSrc_GetWindowCenterY_t			GetWindowCenterY;
	pfnEngSrc_GetViewAngles_t				GetViewAngles;
	pfnEngSrc_SetViewAngles_t				SetViewAngles;
	pfnEngSrc_GetMaxClients_t				GetMaxClients;
	pfnEngSrc_Cvar_SetValue_t				Cvar_SetValue;
	pfnEngSrc_Cmd_Argc_t					Cmd_Argc;
	pfnEngSrc_Cmd_Argv_t					Cmd_Argv;
	pfnEngSrc_Con_Printf_t					Con_Printf;
	pfnEngSrc_Con_DPrintf_t					Con_DPrintf;
	pfnEngSrc_Con_NPrintf_t					Con_NPrintf;
	pfnEngSrc_Con_NXPrintf_t				Con_NXPrintf;
	pfnEngSrc_PhysInfo_ValueForKey_t		PhysInfo_ValueForKey;
	pfnEngSrc_ServerInfo_ValueForKey_t		ServerInfo_ValueForKey;
	pfnEngSrc_GetClientMaxspeed_t			GetClientMaxspeed;
	pfnEngSrc_CheckParm_t					CheckParm;
	pfnEngSrc_Key_Event_t					Key_Event;
	pfnEngSrc_GetMousePosition_t			GetMousePosition;
	pfnEngSrc_IsNoClipping_t				IsNoClipping;
	pfnEngSrc_GetLocalPlayer_t				GetLocalPlayer;
	pfnEngSrc_GetViewModel_t				GetViewModel;
	pfnEngSrc_GetEntityByIndex_t			GetEntityByIndex;
	pfnEngSrc_GetClientTime_t				GetClientTime;
	pfnEngSrc_V_CalcShake_t					V_CalcShake;
	pfnEngSrc_V_ApplyShake_t				V_ApplyShake;
	pfnEngSrc_PM_PointContents_t			PM_PointContents;
	pfnEngSrc_PM_WaterEntity_t				PM_WaterEntity;
	pfnEngSrc_PM_TraceLine_t				PM_TraceLine;
	pfnEngSrc_CL_LoadModel_t				CL_LoadModel;
	pfnEngSrc_CL_CreateVisibleEntity_t		CL_CreateVisibleEntity;
	pfnEngSrc_GetSpritePointer_t			GetSpritePointer;
	pfnEngSrc_pfnPlaySoundByNameAtLocation_t	pfnPlaySoundByNameAtLocation;
	pfnEngSrc_pfnPrecacheEvent_t			pfnPrecacheEvent;
	pfnEngSrc_pfnPlaybackEvent_t			pfnPlaybackEvent;
	pfnEngSrc_pfnWeaponAnim_t				pfnWeaponAnim;
	pfnEngSrc_pfnRandomFloat_t				pfnRandomFloat;
	pfnEngSrc_pfnRandomLong_t				pfnRandomLong;
	pfnEngSrc_pfnHookEvent_t				pfnHookEvent;
	pfnEngSrc_Con_IsVisible_t				Con_IsVisible;
	pfnEngSrc_pfnGetGameDirectory_t			pfnGetGameDirectory;
	pfnEngSrc_pfnGetCvarPointer_t			pfnGetCvarPointer;
	pfnEngSrc_Key_LookupBinding_t			Key_LookupBinding;
	pfnEngSrc_pfnGetLevelName_t				pfnGetLevelName;
	pfnEngSrc_pfnGetScreenFade_t			pfnGetScreenFade;
	pfnEngSrc_pfnSetScreenFade_t			pfnSetScreenFade;
	pfnEngSrc_VGui_GetPanel_t				VGui_GetPanel;
	pfnEngSrc_VGui_ViewportPaintBackground_t	VGui_ViewportPaintBackground;
	pfnEngSrc_COM_LoadFile_t				COM_LoadFile;
	pfnEngSrc_COM_ParseFile_t				COM_ParseFile;
	pfnEngSrc_COM_FreeFile_t				COM_FreeFile;
	struct triangleapi_s* pTriAPI;
	struct efx_api_s* pEfxAPI;
	struct event_api_s* pEventAPI;
	struct demo_api_s* pDemoAPI;
	struct net_api_s* pNetAPI;
	struct IVoiceTweak_s* pVoiceTweak;
	pfnEngSrc_IsSpectateOnly_t				IsSpectateOnly;
	pfnEngSrc_LoadMapSprite_t				LoadMapSprite;
	pfnEngSrc_COM_AddAppDirectoryToSearchPath_t		COM_AddAppDirectoryToSearchPath;
	pfnEngSrc_COM_ExpandFilename_t			COM_ExpandFilename;
	pfnEngSrc_PlayerInfo_ValueForKey_t		PlayerInfo_ValueForKey;
	pfnEngSrc_PlayerInfo_SetValueForKey_t	PlayerInfo_SetValueForKey;
	pfnEngSrc_GetPlayerUniqueID_t			GetPlayerUniqueID;
	pfnEngSrc_GetTrackerIDForPlayer_t		GetTrackerIDForPlayer;
	pfnEngSrc_GetPlayerForTrackerID_t		GetPlayerForTrackerID;
	pfnEngSrc_pfnServerCmdUnreliable_t		pfnServerCmdUnreliable;
	pfnEngSrc_GetMousePos_t					pfnGetMousePos;
	pfnEngSrc_SetMousePos_t					pfnSetMousePos;
	pfnEngSrc_SetMouseEnable_t				pfnSetMouseEnable;
	pfnEngSrc_GetFirstCVarPtr_t				GetFirstCvarPtr;
	pfnEngSrc_GetFirstCmdFunctionHandle_t	GetFirstCmdFunctionHandle;
	pfnEngSrc_GetNextCmdFunctionHandle_t	GetNextCmdFunctionHandle;
	pfnEngSrc_GetCmdFunctionName_t			GetCmdFunctionName;
	pfnEngSrc_GetClientOldTime_t			hudGetClientOldTime;
	pfnEngSrc_GetServerGravityValue_t		hudGetServerGravityValue;
	pfnEngSrc_GetModelByIndex_t				hudGetModelByIndex;
	pfnEngSrc_pfnSetFilterMode_t			pfnSetFilterMode;
	pfnEngSrc_pfnSetFilterColor_t			pfnSetFilterColor;
	pfnEngSrc_pfnSetFilterBrightness_t		pfnSetFilterBrightness;
	pfnEngSrc_pfnSequenceGet_t				pfnSequenceGet;
	pfnEngSrc_pfnSPR_DrawGeneric_t			pfnSPR_DrawGeneric;
	pfnEngSrc_pfnSequencePickSentence_t		pfnSequencePickSentence;
	pfnEngSrc_pfnDrawString_t				pfnDrawString;
	pfnEngSrc_pfnDrawStringReverse_t				pfnDrawStringReverse;
	pfnEngSrc_LocalPlayerInfo_ValueForKey_t		LocalPlayerInfo_ValueForKey;
	pfnEngSrc_pfnVGUI2DrawCharacter_t		pfnVGUI2DrawCharacter;
	pfnEngSrc_pfnVGUI2DrawCharacterAdd_t	pfnVGUI2DrawCharacterAdd;
	pfnEngSrc_COM_GetApproxWavePlayLength	COM_GetApproxWavePlayLength;
	pfnEngSrc_pfnGetCareerUI_t				pfnGetCareerUI;
	pfnEngSrc_Cvar_Set_t					Cvar_Set;
	pfnEngSrc_pfnIsPlayingCareerMatch_t		pfnIsCareerMatch;
	pfnEngSrc_pfnPlaySoundVoiceByName_t	pfnPlaySoundVoiceByName;
	pfnEngSrc_pfnPrimeMusicStream_t		pfnPrimeMusicStream;
	pfnEngSrc_GetAbsoluteTime_t				GetAbsoluteTime;
	pfnEngSrc_pfnProcessTutorMessageDecayBuffer_t		pfnProcessTutorMessageDecayBuffer;
	pfnEngSrc_pfnConstructTutorMessageDecayBuffer_t		pfnConstructTutorMessageDecayBuffer;
	pfnEngSrc_pfnResetTutorMessageDecayData_t		pfnResetTutorMessageDecayData;
	pfnEngSrc_pfnPlaySoundByNameAtPitch_t	pfnPlaySoundByNameAtPitch;
	pfnEngSrc_pfnFillRGBABlend_t					pfnFillRGBABlend;
	pfnEngSrc_pfnGetAppID_t					pfnGetAppID;
	pfnEngSrc_pfnGetAliases_t				pfnGetAliasList;
	pfnEngSrc_pfnVguiWrap2_GetMouseDelta_t pfnVguiWrap2_GetMouseDelta;
} cl_enginefunc_t;

//==============
// SERVER PART
//==============

// MD5 Hash
typedef struct
{
	unsigned int buf[4];
	unsigned int bits[2];
	unsigned char in[64];
} MD5Context_t;


#ifdef _WIN32
typedef uint32 CRC32_t;
#else
typedef uint32 CRC32_t;
#endif

#define MAX_QPATH 64    // Must match value in quakedefs.h

/////////////////
// Customization
// passed to pfnPlayerCustomization
// For automatic downloading.
typedef enum
{
	t_sound = 0,
	t_skin,
	t_model,
	t_decal,
	t_generic,
	t_eventscript,
	t_world,		// Fake type for world, is really t_model
} resourcetype_t;


typedef struct
{
	int				size;
} _resourceinfo_t;

typedef struct resourceinfo_s
{
	_resourceinfo_t info[8];
} resourceinfo_t;

#define RES_FATALIFMISSING (1<<0)   // Disconnect if we can't get this file.
#define RES_WASMISSING     (1<<1)   // Do we have the file locally, did we get it ok?
#define RES_CUSTOM         (1<<2)   // Is this resource one that corresponds to another player's customization
// or is it a server startup resource.
#define RES_REQUESTED	   (1<<3)	// Already requested a download of this one
#define RES_PRECACHED	   (1<<4)	// Already precached
#define RES_ALWAYS		   (1<<5)	// download always even if available on client	
#define RES_CHECKFILE	   (1<<7)	// check file on client

typedef struct resource_s
{
	char              szFileName[MAX_QPATH]; // File name to download/precache.
	resourcetype_t    type;                // t_sound, t_skin, t_model, t_decal.
	int               nIndex;              // For t_decals
	int               nDownloadSize;       // Size in Bytes if this must be downloaded.
	unsigned char     ucFlags;

	// For handling client to client resource propagation
	unsigned char     rgucMD5_hash[16];    // To determine if we already have it.
	unsigned char     playernum;           // Which player index this resource is associated with, if it's a custom resource.

	unsigned char	  rguc_reserved[32]; // For future expansion
	struct resource_s* pNext;              // Next in chain.
	struct resource_s* pPrev;
} resource_t;

typedef struct customization_s
{
	qboolean bInUse;     // Is this customization in use;
	resource_t resource; // The resource_t for this customization
	qboolean bTranslated; // Has the raw data been translated into a useable format?  
	//  (e.g., raw decal .wad make into texture_t *)
	int        nUserData1; // Customization specific data
	int        nUserData2; // Customization specific data
	void* pInfo;          // Buffer that holds the data structure that references the data (e.g., the cachewad_t)
	void* pBuffer;       // Buffer that holds the data for the customization (the raw .wad data)
	struct customization_s* pNext; // Next in chain
} customization_t;

#define FCUST_FROMHPAK		( 1<<0 )
#define FCUST_WIPEDATA		( 1<<1 )
#define FCUST_IGNOREINIT	( 1<<2 )

typedef enum
{
	at_notice,
	at_console,		// same as at_notice, but forces a ConPrintf, not a message box
	at_aiconsole,	// same as at_console, but only shown if developer level is 2!
	at_warning,
	at_error,
	at_logged		// Server print to console ( only in multiplayer games ).
} ALERT_TYPE;

// 4-22-98  JOHN: added for use in pfnClientPrintf
typedef enum
{
	print_console,
	print_center,
	print_chat,
} PRINT_TYPE;

// For integrity checking of content on clients
typedef enum
{
	force_exactfile,					// File on client must exactly match server's file
	force_model_samebounds,				// For model files only, the geometry must fit in the same bbox
	force_model_specifybounds,			// For model files only, the geometry must fit in the specified bbox
	force_model_specifybounds_if_avail,	// For Steam model files only, the geometry must fit in the specified bbox (if the file is available)
} FORCE_TYPE;

// Returned by TraceLine
typedef struct
{
	int		fAllSolid;			// if true, plane is not valid
	int		fStartSolid;		// if true, the initial point was in a solid area
	int		fInOpen;
	int		fInWater;
	float	flFraction;			// time completed, 1.0 = didn't hit anything
	vec3_t	vecEndPos;			// final position
	float	flPlaneDist;
	vec3_t	vecPlaneNormal;		// surface normal at impact
	edict_t* pHit;				// entity the surface is on
	int		iHitgroup;			// 0 == generic, non zero is specific body part
} TraceResult;

// CD audio status
typedef struct
{
	int	fPlaying;// is sound playing right now?
	int	fWasPlaying;// if not, CD is paused if WasPlaying is true.
	int	fInitialized;
	int	fEnabled;
	int	fPlayLooping;
	float	cdvolume;
	//BYTE 	remap[100];
	int	fCDRom;
	int	fPlayTrack;
} CDStatus;


// Engine hands this to DLLs for functionality callbacks
typedef struct enginefuncs_s
{
	int			(*pfnPrecacheModel)			(char* s);
	int			(*pfnPrecacheSound)			(char* s);
	void		(*pfnSetModel)				(edict_t* e, const char* m);
	int			(*pfnModelIndex)			(const char* m);
	int			(*pfnModelFrames)			(int modelIndex);
	void		(*pfnSetSize)				(edict_t* e, const float* rgflMin, const float* rgflMax);
	void		(*pfnChangeLevel)			(char* s1, char* s2);
	void		(*pfnGetSpawnParms)			(edict_t* ent);
	void		(*pfnSaveSpawnParms)		(edict_t* ent);
	float		(*pfnVecToYaw)				(const float* rgflVector);
	void		(*pfnVecToAngles)			(const float* rgflVectorIn, float* rgflVectorOut);
	void		(*pfnMoveToOrigin)			(edict_t* ent, const float* pflGoal, float dist, int iMoveType);
	void		(*pfnChangeYaw)				(edict_t* ent);
	void		(*pfnChangePitch)			(edict_t* ent);
	edict_t* (*pfnFindEntityByString)	(edict_t* pEdictStartSearchAfter, const char* pszField, const char* pszValue);
	int			(*pfnGetEntityIllum)		(edict_t* pEnt);
	edict_t* (*pfnFindEntityInSphere)	(edict_t* pEdictStartSearchAfter, const float* org, float rad);
	edict_t* (*pfnFindClientInPVS)		(edict_t* pEdict);
	edict_t* (*pfnEntitiesInPVS)			(edict_t* pplayer);
	void		(*pfnMakeVectors)			(const float* rgflVector);
	void		(*pfnAngleVectors)			(const float* rgflVector, float* forward, float* right, float* up);
	edict_t* (*pfnCreateEntity)			(void);
	void		(*pfnRemoveEntity)			(edict_t* e);
	edict_t* (*pfnCreateNamedEntity)		(int className);
	void		(*pfnMakeStatic)			(edict_t* ent);
	int			(*pfnEntIsOnFloor)			(edict_t* e);
	int			(*pfnDropToFloor)			(edict_t* e);
	int			(*pfnWalkMove)				(edict_t* ent, float yaw, float dist, int iMode);
	void		(*pfnSetOrigin)				(edict_t* e, const float* rgflOrigin);
	void		(*pfnEmitSound)				(edict_t* entity, int channel, const char* sample, /*int*/float volume, float attenuation, int fFlags, int pitch);
	void		(*pfnEmitAmbientSound)		(edict_t* entity, float* pos, const char* samp, float vol, float attenuation, int fFlags, int pitch);
	void		(*pfnTraceLine)				(const float* v1, const float* v2, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
	void		(*pfnTraceToss)				(edict_t* pent, edict_t* pentToIgnore, TraceResult* ptr);
	int			(*pfnTraceMonsterHull)		(edict_t* pEdict, const float* v1, const float* v2, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr);
	void		(*pfnTraceHull)				(const float* v1, const float* v2, int fNoMonsters, int hullNumber, edict_t* pentToSkip, TraceResult* ptr);
	void		(*pfnTraceModel)			(const float* v1, const float* v2, int hullNumber, edict_t* pent, TraceResult* ptr);
	const char* (*pfnTraceTexture)			(edict_t* pTextureEntity, const float* v1, const float* v2);
	void		(*pfnTraceSphere)			(const float* v1, const float* v2, int fNoMonsters, float radius, edict_t* pentToSkip, TraceResult* ptr);
	void		(*pfnGetAimVector)			(edict_t* ent, float speed, float* rgflReturn);
	void		(*pfnServerCommand)			(char* str);
	void		(*pfnServerExecute)			(void);
	void		(*pfnClientCommand)			(edict_t* pEdict, char* szFmt, ...);
	void		(*pfnParticleEffect)		(const float* org, const float* dir, float color, float count);
	void		(*pfnLightStyle)			(int style, char* val);
	int			(*pfnDecalIndex)			(const char* name);
	int			(*pfnPointContents)			(const float* rgflVector);
	void		(*pfnMessageBegin)			(int msg_dest, int msg_type, const float* pOrigin, edict_t* ed);
	void		(*pfnMessageEnd)			(void);
	void		(*pfnWriteByte)				(int iValue);
	void		(*pfnWriteChar)				(int iValue);
	void		(*pfnWriteShort)			(int iValue);
	void		(*pfnWriteLong)				(int iValue);
	void		(*pfnWriteAngle)			(float flValue);
	void		(*pfnWriteCoord)			(float flValue);
	void		(*pfnWriteString)			(const char* sz);
	void		(*pfnWriteEntity)			(int iValue);
	void		(*pfnCVarRegister)			(cvar_t* pCvar);
	float		(*pfnCVarGetFloat)			(const char* szVarName);
	const char* (*pfnCVarGetString)			(const char* szVarName);
	void		(*pfnCVarSetFloat)			(const char* szVarName, float flValue);
	void		(*pfnCVarSetString)			(const char* szVarName, const char* szValue);
	void		(*pfnAlertMessage)			(ALERT_TYPE atype, char* szFmt, ...);
	void		(*pfnEngineFprintf)			(void* pfile, char* szFmt, ...);
	void* (*pfnPvAllocEntPrivateData)	(edict_t* pEdict, int32 cb);
	void* (*pfnPvEntPrivateData)		(edict_t* pEdict);
	void		(*pfnFreeEntPrivateData)	(edict_t* pEdict);
	const char* (*pfnSzFromIndex)			(int iString);
	int			(*pfnAllocString)			(const char* szValue);
	struct entvars_s* (*pfnGetVarsOfEnt)			(edict_t* pEdict);
	edict_t* (*pfnPEntityOfEntOffset)	(int iEntOffset);
	int			(*pfnEntOffsetOfPEntity)	(const edict_t* pEdict);
	int			(*pfnIndexOfEdict)			(const edict_t* pEdict);
	edict_t* (*pfnPEntityOfEntIndex)		(int iEntIndex);
	edict_t* (*pfnFindEntityByVars)		(struct entvars_s* pvars);
	void* (*pfnGetModelPtr)			(edict_t* pEdict);
	int			(*pfnRegUserMsg)			(const char* pszName, int iSize);
	void		(*pfnAnimationAutomove)		(const edict_t* pEdict, float flTime);
	void		(*pfnGetBonePosition)		(const edict_t* pEdict, int iBone, float* rgflOrigin, float* rgflAngles);
	uint32(*pfnFunctionFromName)	(const char* pName);
	const char* (*pfnNameForFunction)		(uint32 function);
	void		(*pfnClientPrintf)			(edict_t* pEdict, PRINT_TYPE ptype, const char* szMsg); // JOHN: engine callbacks so game DLL can print messages to individual clients
	void		(*pfnServerPrint)			(const char* szMsg);
	const char* (*pfnCmd_Args)				(void);		// these 3 added 
	const char* (*pfnCmd_Argv)				(int argc);	// so game DLL can easily 
	int			(*pfnCmd_Argc)				(void);		// access client 'cmd' strings
	void		(*pfnGetAttachment)			(const edict_t* pEdict, int iAttachment, float* rgflOrigin, float* rgflAngles);
	void		(*pfnCRC32_Init)			(CRC32_t* pulCRC);
	void        (*pfnCRC32_ProcessBuffer)   (CRC32_t* pulCRC, void* p, int len);
	void		(*pfnCRC32_ProcessByte)     (CRC32_t* pulCRC, unsigned char ch);
	CRC32_t(*pfnCRC32_Final)			(CRC32_t pulCRC);
	int32(*pfnRandomLong)			(int32  lLow, int32  lHigh);
	float		(*pfnRandomFloat)			(float flLow, float flHigh);
	void		(*pfnSetView)				(const edict_t* pClient, const edict_t* pViewent);
	float		(*pfnTime)					(void);
	void		(*pfnCrosshairAngle)		(const edict_t* pClient, float pitch, float yaw);
	byte* (*pfnLoadFileForMe)         (char* filename, int* pLength);
	void        (*pfnFreeFile)              (void* buffer);
	void        (*pfnEndSection)            (const char* pszSectionName); // trigger_endsection
	int 		(*pfnCompareFileTime)       (char* filename1, char* filename2, int* iCompare);
	void        (*pfnGetGameDir)            (char* szGetGameDir);
	void		(*pfnCvar_RegisterVariable) (cvar_t* variable);
	void        (*pfnFadeClientVolume)      (const edict_t* pEdict, int fadePercent, int fadeOutSeconds, int holdTime, int fadeInSeconds);
	void        (*pfnSetClientMaxspeed)     (const edict_t* pEdict, float fNewMaxspeed);
	edict_t* (*pfnCreateFakeClient)		(const char* netname);	// returns NULL if fake client can't be created
	void		(*pfnRunPlayerMove)			(edict_t* fakeclient, const float* viewangles, float forwardmove, float sidemove, float upmove, unsigned short buttons, byte impulse, byte msec);
	int			(*pfnNumberOfEntities)		(void);
	char* (*pfnGetInfoKeyBuffer)		(edict_t* e);	// passing in NULL gets the serverinfo
	char* (*pfnInfoKeyValue)			(char* infobuffer, char* key);
	void		(*pfnSetKeyValue)			(char* infobuffer, char* key, char* value);
	void		(*pfnSetClientKeyValue)		(int clientIndex, char* infobuffer, char* key, char* value);
	int			(*pfnIsMapValid)			(char* filename);
	void		(*pfnStaticDecal)			(const float* origin, int decalIndex, int entityIndex, int modelIndex);
	int			(*pfnPrecacheGeneric)		(char* s);
	int			(*pfnGetPlayerUserId)		(edict_t* e); // returns the server assigned userid for this player.  useful for logging frags, etc.  returns -1 if the edict couldn't be found in the list of clients
	void		(*pfnBuildSoundMsg)			(edict_t* entity, int channel, const char* sample, /*int*/float volume, float attenuation, int fFlags, int pitch, int msg_dest, int msg_type, const float* pOrigin, edict_t* ed);
	int			(*pfnIsDedicatedServer)		(void);// is this a dedicated server?
	cvar_t* (*pfnCVarGetPointer)		(const char* szVarName);
	unsigned int (*pfnGetPlayerWONId)		(edict_t* e); // returns the server assigned WONid for this player.  useful for logging frags, etc.  returns -1 if the edict couldn't be found in the list of clients

	// YWB 8/1/99 TFF Physics additions
	void		(*pfnInfo_RemoveKey)		(char* s, const char* key);
	const char* (*pfnGetPhysicsKeyValue)	(const edict_t* pClient, const char* key);
	void		(*pfnSetPhysicsKeyValue)	(const edict_t* pClient, const char* key, const char* value);
	const char* (*pfnGetPhysicsInfoString)	(const edict_t* pClient);
	unsigned short (*pfnPrecacheEvent)		(int type, const char* psz);
	void		(*pfnPlaybackEvent)			(int flags, const edict_t* pInvoker, unsigned short eventindex, float delay, float* origin, float* angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);

	unsigned char* (*pfnSetFatPVS)			(float* org);
	unsigned char* (*pfnSetFatPAS)			(float* org);

	int			(*pfnCheckVisibility)		(const edict_t* entity, unsigned char* pset);

	void		(*pfnDeltaSetField)			(struct delta_s* pFields, const char* fieldname);
	void		(*pfnDeltaUnsetField)		(struct delta_s* pFields, const char* fieldname);
	void		(*pfnDeltaAddEncoder)		(char* name, void (*conditionalencode)(struct delta_s* pFields, const unsigned char* from, const unsigned char* to));
	int			(*pfnGetCurrentPlayer)		(void);
	int			(*pfnCanSkipPlayer)			(const edict_t* player);
	int			(*pfnDeltaFindField)		(struct delta_s* pFields, const char* fieldname);
	void		(*pfnDeltaSetFieldByIndex)	(struct delta_s* pFields, int fieldNumber);
	void		(*pfnDeltaUnsetFieldByIndex)(struct delta_s* pFields, int fieldNumber);

	void		(*pfnSetGroupMask)			(int mask, int op);

	int			(*pfnCreateInstancedBaseline) (int classname, struct entity_state_s* baseline);
	void		(*pfnCvar_DirectSet)		(struct cvar_s* var, char* value);

	// Forces the client and server to be running with the same version of the specified file
	//  ( e.g., a player model ).
	// Calling this has no effect in single player
	void		(*pfnForceUnmodified)		(FORCE_TYPE type, float* mins, float* maxs, const char* filename);

	void		(*pfnGetPlayerStats)		(const edict_t* pClient, int* ping, int* packet_loss);

	void		(*pfnAddServerCommand)		(char* cmd_name, void (*function) (void));

	// For voice communications, set which clients hear eachother.
	// NOTE: these functions take player entity indices (starting at 1).
	qboolean(*pfnVoice_GetClientListening)(int iReceiver, int iSender);
	qboolean(*pfnVoice_SetClientListening)(int iReceiver, int iSender, qboolean bListen);

	const char* (*pfnGetPlayerAuthId)		(edict_t* e);

	// PSV: Added for CZ training map
//	const char *(*pfnKeyNameForBinding)		( const char* pBinding );

	sequenceEntry_s* (*pfnSequenceGet)			(const char* fileName, const char* entryName);
	sentenceEntry_s* (*pfnSequencePickSentence)	(const char* groupName, int pickMethod, int* picked);

	// LH: Give access to filesize via filesystem
	int			(*pfnGetFileSize)			(char* filename);

	unsigned int (*pfnGetApproxWavePlayLen) (const char* filepath);
	// MDC: Added for CZ career-mode
	int			(*pfnIsCareerMatch)			(void);

	// BGC: return the number of characters of the localized string referenced by using "label"
	int			(*pfnGetLocalizedStringLength)(const char* label);

	// BGC: added to facilitate persistent storage of tutor message decay values for
	// different career game profiles.  Also needs to persist regardless of mp.dll being
	// destroyed and recreated.
	void (*pfnRegisterTutorMessageShown)(int mid);
	int (*pfnGetTimesTutorMessageShown)(int mid);
	void (*ProcessTutorMessageDecayBuffer)(int* buffer, int bufferLength);
	void (*ConstructTutorMessageDecayBuffer)(int* buffer, int bufferLength);
	void (*ResetTutorMessageDecayData)(void);

	void (*pfnQueryClientCvarValue)(const edict_t* player, const char* cvarName);
	void (*pfnQueryClientCvarValue2)(const edict_t* player, const char* cvarName, int requestID);
	int (*pfnCheckParm)(const char* pchCmdLineToken, char** ppnext);
} enginefuncs_t;


// ONLY ADD NEW FUNCTIONS TO THE END OF THIS STRUCT.  INTERFACE VERSION IS FROZEN AT 138

// Passed to pfnKeyValue
typedef struct KeyValueData_s
{
	char* szClassName;	// in: entity classname
	char* szKeyName;		// in: name of key
	char* szValue;		// in: value of key
	int32	fHandled;		// out: DLL sets to true if key-value pair was understood
} KeyValueData;


typedef struct
{
	char		mapName[32];
	char		landmarkName[32];
	edict_t* pentLandmark;
	vec3_t		vecLandmarkOrigin;
} LEVELLIST;
#define MAX_LEVEL_CONNECTIONS	16		// These are encoded in the lower 16bits of ENTITYTABLE->flags

typedef struct
{
	int			id;				// Ordinal ID of this entity (used for entity <--> pointer conversions)
	edict_t* pent;			// Pointer to the in-game entity

	int			location;		// Offset from the base data of this entity
	int			size;			// Byte size of this entity's data
	int			flags;			// This could be a short -- bit mask of transitions that this entity is in the PVS of
	string_t	classname;		// entity class name

} ENTITYTABLE;

#define FENTTABLE_PLAYER		0x80000000
#define FENTTABLE_REMOVED		0x40000000
#define FENTTABLE_MOVEABLE		0x20000000
#define FENTTABLE_GLOBAL		0x10000000

typedef struct saverestore_s SAVERESTOREDATA;

#ifdef _WIN32
typedef
#endif
struct saverestore_s
{
	char* pBaseData;		// Start of all entity save data
	char* pCurrentData;	// Current buffer pointer for sequential access
	int			size;			// Current data size
	int			bufferSize;		// Total space for data
	int			tokenSize;		// Size of the linear list of tokens
	int			tokenCount;		// Number of elements in the pTokens table
	char** pTokens;		// Hash table of entity strings (sparse)
	int			currentIndex;	// Holds a global entity table ID
	int			tableCount;		// Number of elements in the entity table
	int			connectionCount;// Number of elements in the levelList[]
	ENTITYTABLE* pTable;		// Array of ENTITYTABLE elements (1 for each entity)
	LEVELLIST	levelList[MAX_LEVEL_CONNECTIONS];		// List of connections from this level

	// smooth transition
	int			fUseLandmark;
	char		szLandmarkName[20];// landmark we'll spawn near in next level
	vec3_t		vecLandmarkOffset;// for landmark transitions
	float		time;
	char		szCurrentMapName[32];	// To check global entities

}
#ifdef _WIN32
SAVERESTOREDATA
#endif
;

typedef enum _fieldtypes
{
	FIELD_FLOAT = 0,		// Any floating point value
	FIELD_STRING,			// A string ID (return from ALLOC_STRING)
	FIELD_ENTITY,			// An entity offset (EOFFSET)
	FIELD_CLASSPTR,			// CBaseEntity *
	FIELD_EHANDLE,			// Entity handle
	FIELD_EVARS,			// EVARS *
	FIELD_EDICT,			// edict_t *, or edict_t *  (same thing)
	FIELD_VECTOR,			// Any vector
	FIELD_POSITION_VECTOR,	// A world coordinate (these are fixed up across level transitions automagically)
	FIELD_POINTER,			// Arbitrary data pointer... to be removed, use an array of FIELD_CHARACTER
	FIELD_INTEGER,			// Any integer or enum
	FIELD_FUNCTION,			// A class function pointer (Think, Use, etc)
	FIELD_BOOLEAN,			// boolean, implemented as an int, I may use this as a hint for compression
	FIELD_SHORT,			// 2 byte integer
	FIELD_CHARACTER,		// a byte
	FIELD_TIME,				// a floating point time (these are fixed up automatically too!)
	FIELD_MODELNAME,		// Engine string that is a model name (needs precache)
	FIELD_SOUNDNAME,		// Engine string that is a sound name (needs precache)

	FIELD_TYPECOUNT,		// MUST BE LAST
} FIELDTYPE;

#if !defined(offsetof)  && !defined(GNUC)
#define offsetof(s,m)	(size_t)&(((s *)0)->m)
#endif

#define _FIELD(type,name,fieldtype,count,flags)		{ fieldtype, #name, offsetof(type, name), count, flags }
#define DEFINE_FIELD(type,name,fieldtype)			_FIELD(type, name, fieldtype, 1, 0)
#define DEFINE_ARRAY(type,name,fieldtype,count)		_FIELD(type, name, fieldtype, count, 0)
#define DEFINE_ENTITY_FIELD(name,fieldtype)			_FIELD(entvars_t, name, fieldtype, 1, 0 )
#define DEFINE_ENTITY_GLOBAL_FIELD(name,fieldtype)	_FIELD(entvars_t, name, fieldtype, 1, FTYPEDESC_GLOBAL )
#define DEFINE_GLOBAL_FIELD(type,name,fieldtype)	_FIELD(type, name, fieldtype, 1, FTYPEDESC_GLOBAL )


#define FTYPEDESC_GLOBAL			0x0001		// This field is masked for global entity save/restore

#define MAX_PHYSINFO_STRING 256

typedef struct movevars_s movevars_t;

struct movevars_s
{
	float	gravity;           // Gravity for map
	float	stopspeed;         // Deceleration when not moving
	float	maxspeed;          // Max allowed speed
	float	spectatormaxspeed;
	float	accelerate;        // Acceleration factor
	float	airaccelerate;     // Same for when in open air
	float	wateraccelerate;   // Same for when in water
	float	friction;
	float   edgefriction;	   // Extra friction near dropofs 
	float	waterfriction;     // Less in water
	float	entgravity;        // 1.0
	float   bounce;            // Wall bounce value. 1.0
	float   stepsize;          // sv_stepsize;
	float   maxvelocity;       // maximum server velocity.
	float	zmax;			   // Max z-buffer range (for GL)
	float	waveHeight;		   // Water wave height (for GL)
	qboolean footsteps;        // Play footstep sounds
	char	skyName[32];	   // Name of the sky map
	float	rollangle;
	float	rollspeed;
	float	skycolor_r;			// Sky color
	float	skycolor_g;			// 
	float	skycolor_b;			//
	float	skyvec_x;			// Sky vector
	float	skyvec_y;			// 
	float	skyvec_z;			// 
};

extern movevars_t movevars;

typedef struct playermove_s playermove_t;

struct playermove_s
{
	int				player_index;  // So we don't try to run the PM_CheckStuck nudging too quickly.
	qboolean		server;        // For debugging, are we running physics code on server side?

	qboolean		multiplayer;   // 1 == multiplayer server
	float			time;          // realtime on host, for reckoning duck timing
	float			frametime;	   // Duration of this frame

	vec3_t			forward, right, up; // Vectors for angles
	// player state
	vec3_t			origin;        // Movement origin.
	vec3_t			angles;        // Movement view angles.
	vec3_t			oldangles;     // Angles before movement view angles were looked at.
	vec3_t			velocity;      // Current movement direction.
	vec3_t			movedir;       // For waterjumping, a forced forward velocity so we can fly over lip of ledge.
	vec3_t			basevelocity;  // Velocity of the conveyor we are standing, e.g.

	// For ducking/dead
	vec3_t			view_ofs;      // Our eye position.
	float			flDuckTime;    // Time we started duck
	qboolean		bInDuck;       // In process of ducking or ducked already?

	// For walking/falling
	int				flTimeStepSound;  // Next time we can play a step sound
	int				iStepLeft;

	float			flFallVelocity;
	vec3_t			punchangle;

	float			flSwimTime;

	float			flNextPrimaryAttack;

	int				effects;		// MUZZLE FLASH, e.g.

	int				flags;         // FL_ONGROUND, FL_DUCKING, etc.
	int				usehull;       // 0 = regular player hull, 1 = ducked player hull, 2 = point hull
	float			gravity;       // Our current gravity and friction.
	float			friction;
	int				oldbuttons;    // Buttons last usercmd
	float			waterjumptime; // Amount of time left in jumping out of water cycle.
	qboolean		dead;          // Are we a dead player?
	int				deadflag;
	int				spectator;     // Should we use spectator physics model?
	int				movetype;      // Our movement type, NOCLIP, WALK, FLY

	int				onground;
	int				waterlevel;
	int				watertype;
	int				oldwaterlevel;

	char			sztexturename[256];
	char			chtexturetype;

	float			maxspeed;
	float			clientmaxspeed; // Player specific maxspeed

	// For mods
	int				iuser1;
	int				iuser2;
	int				iuser3;
	int				iuser4;
	float			fuser1;
	float			fuser2;
	float			fuser3;
	float			fuser4;
	vec3_t			vuser1;
	vec3_t			vuser2;
	vec3_t			vuser3;
	vec3_t			vuser4;
	// world state
	// Number of entities to clip against.
	int				numphysent;
	physent_t		physents[MAX_PHYSENTS];
	// Number of momvement entities (ladders)
	int				nummoveent;
	// just a list of ladders
	physent_t		moveents[MAX_MOVEENTS];

	// All things being rendered, for tracing against things you don't actually collide with
	int				numvisent;
	physent_t		visents[MAX_PHYSENTS];

	// input to run through physics.
	usercmd_t		cmd;

	// Trace results for objects we collided with.
	int				numtouch;
	pmtrace_t		touchindex[MAX_PHYSENTS];

	char			physinfo[MAX_PHYSINFO_STRING]; // Physics info string

	struct movevars_s* movevars;
	vec3_t player_mins[4];
	vec3_t player_maxs[4];

	const char* (*PM_Info_ValueForKey) (const char* s, const char* key);
	void			(*PM_Particle)(vec3_t origin, int color, float life, int zpos, int zvel);
	int				(*PM_TestPlayerPosition) (vec3_t pos, pmtrace_t* ptrace);
	void			(*Con_NPrintf)(int idx, char* fmt, ...);
	void			(*Con_DPrintf)(char* fmt, ...);
	void			(*Con_Printf)(char* fmt, ...);
	double			(*Sys_FloatTime)(void);
	void			(*PM_StuckTouch)(int hitent, pmtrace_t* ptraceresult);
	int				(*PM_PointContents) (vec3_t p, int* truecontents);
	int				(*PM_TruePointContents) (vec3_t p);
	int				(*PM_HullPointContents) (struct hull_s* hull, int num, vec3_t p);
	pmtrace_t(*PM_PlayerTrace) (vec3_t start, vec3_t end, int traceFlags, int ignore_pe);
	struct pmtrace_s* (*PM_TraceLine)(float* start, float* end, int flags, int usehulll, int ignore_pe);
	int32(*RandomLong)(int32 lLow, int32 lHigh);
	float			(*RandomFloat)(float flLow, float flHigh);
	int				(*PM_GetModelType)(struct model_s* mod);
	void			(*PM_GetModelBounds)(struct model_s* mod, vec3_t mins, vec3_t maxs);
	void* (*PM_HullForBsp)(physent_t* pe, vec3_t offset);
	float			(*PM_TraceModel)(physent_t* pEnt, vec3_t start, vec3_t end, trace_t* trace);
	int				(*COM_FileSize)(char* filename);
	byte* (*COM_LoadFile) (char* path, int usehunk, int* pLength);
	void			(*COM_FreeFile) (void* buffer);
	char* (*memfgets)(byte* pMemFile, int fileSize, int* pFilePos, char* pBuffer, int bufferSize);
	qboolean		runfuncs;
	void			(*PM_PlaySound) (int channel, const char* sample, float volume, float attenuation, int fFlags, int pitch);
	const char* (*PM_TraceTexture) (int ground, vec3_t vstart, vec3_t vend);
	void			(*PM_PlaybackEventFull) (int flags, int clientindex, unsigned short eventindex, float delay, float* origin, float* angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);
};

typedef struct
{
	FIELDTYPE		fieldType;
	char* fieldName;
	int				fieldOffset;
	short			fieldSize;
	short			flags;
} TYPEDESCRIPTION;

#undef ARRAYSIZE
#define ARRAYSIZE(p)		(sizeof(p)/sizeof(p[0]))

typedef struct
{
	// Initialize/shutdown the game (one-time call after loading of game .dll )
	void			(*pfnGameInit)			(void);
	int				(*pfnSpawn)				(edict_t* pent);
	void			(*pfnThink)				(edict_t* pent);
	void			(*pfnUse)				(edict_t* pentUsed, edict_t* pentOther);
	void			(*pfnTouch)				(edict_t* pentTouched, edict_t* pentOther);
	void			(*pfnBlocked)			(edict_t* pentBlocked, edict_t* pentOther);
	void			(*pfnKeyValue)			(edict_t* pentKeyvalue, KeyValueData* pkvd);
	void			(*pfnSave)				(edict_t* pent, SAVERESTOREDATA* pSaveData);
	int 			(*pfnRestore)			(edict_t* pent, SAVERESTOREDATA* pSaveData, int globalEntity);
	void			(*pfnSetAbsBox)			(edict_t* pent);

	void			(*pfnSaveWriteFields)	(SAVERESTOREDATA*, const char*, void*, TYPEDESCRIPTION*, int);
	void			(*pfnSaveReadFields)	(SAVERESTOREDATA*, const char*, void*, TYPEDESCRIPTION*, int);

	void			(*pfnSaveGlobalState)		(SAVERESTOREDATA*);
	void			(*pfnRestoreGlobalState)	(SAVERESTOREDATA*);
	void			(*pfnResetGlobalState)		(void);

	qboolean(*pfnClientConnect)		(edict_t* pEntity, const char* pszName, const char* pszAddress, char szRejectReason[128]);

	void			(*pfnClientDisconnect)	(edict_t* pEntity);
	void			(*pfnClientKill)		(edict_t* pEntity);
	void			(*pfnClientPutInServer)	(edict_t* pEntity);
	void			(*pfnClientCommand)		(edict_t* pEntity);
	void			(*pfnClientUserInfoChanged)(edict_t* pEntity, char* infobuffer);

	void			(*pfnServerActivate)	(edict_t* pEdictList, int edictCount, int clientMax);
	void			(*pfnServerDeactivate)	(void);

	void			(*pfnPlayerPreThink)	(edict_t* pEntity);
	void			(*pfnPlayerPostThink)	(edict_t* pEntity);

	void			(*pfnStartFrame)		(void);
	void			(*pfnParmsNewLevel)		(void);
	void			(*pfnParmsChangeLevel)	(void);

	// Returns string describing current .dll.  E.g., TeamFotrress 2, Half-Life
	const char* (*pfnGetGameDescription)(void);

	// Notify dll about a player customization.
	void            (*pfnPlayerCustomization) (edict_t* pEntity, customization_t* pCustom);

	// Spectator funcs
	void			(*pfnSpectatorConnect)		(edict_t* pEntity);
	void			(*pfnSpectatorDisconnect)	(edict_t* pEntity);
	void			(*pfnSpectatorThink)		(edict_t* pEntity);

	// Notify game .dll that engine is going to shut down.  Allows mod authors to set a breakpoint.
	void			(*pfnSys_Error)			(const char* error_string);

	void			(*pfnPM_Move) (struct playermove_s* ppmove, qboolean server);
	void			(*pfnPM_Init) (struct playermove_s* ppmove);
	char			(*pfnPM_FindTextureType)(char* name);
	void			(*pfnSetupVisibility)(struct edict_s* pViewEntity, struct edict_s* pClient, unsigned char** pvs, unsigned char** pas);
	void			(*pfnUpdateClientData) (const struct edict_s* ent, int sendweapons, struct clientdata_s* cd);
	int				(*pfnAddToFullPack)(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet);
	void			(*pfnCreateBaseline) (int player, int eindex, struct entity_state_s* baseline, struct edict_s* entity, int playermodelindex, vec3_t player_mins, vec3_t player_maxs);
	void			(*pfnRegisterEncoders)	(void);
	int				(*pfnGetWeaponData)		(struct edict_s* player, struct weapon_data_s* info);

	void			(*pfnCmdStart)			(const edict_t* player, const struct usercmd_s* cmd, unsigned int random_seed);
	void			(*pfnCmdEnd)			(const edict_t* player);

	// Return 1 if the packet is valid.  Set response_buffer_size if you want to send a response packet.  Incoming, it holds the max
	//  size of the response_buffer, so you must zero it out if you choose not to respond.
	int				(*pfnConnectionlessPacket)	(const struct netadr_s* net_from, const char* args, char* response_buffer, int* response_buffer_size);

	// Enumerates player hulls.  Returns 0 if the hull number doesn't exist, 1 otherwise
	int				(*pfnGetHullBounds)	(int hullnumber, float* mins, float* maxs);

	// Create baselines for certain "unplaced" items.
	void			(*pfnCreateInstancedBaselines) (void);

	// One of the pfnForceUnmodified files failed the consistency check for the specified player
	// Return 0 to allow the client to continue, 1 to force immediate disconnection ( with an optional disconnect message of up to 256 characters )
	int				(*pfnInconsistentFile)(const struct edict_s* player, const char* filename, char* disconnect_message);

	// The game .dll should return 1 if lag compensation should be allowed ( could also just set
	//  the sv_unlag cvar.
	// Most games right now should return 0, until client-side weapon prediction code is written
	//  and tested for them.
	int				(*pfnAllowLagCompensation)(void);
} DLL_FUNCTIONS;

// Current version.
#define NEW_DLL_FUNCTIONS_VERSION	1

typedef struct
{
	// Called right before the object's memory is freed. 
	// Calls its destructor.
	void			(*pfnOnFreeEntPrivateData)(edict_t* pEnt);
	void			(*pfnGameShutdown)(void);
	int				(*pfnShouldCollide)(edict_t* pentTouched, edict_t* pentOther);
	void			(*pfnCvarValue)(const edict_t* pEnt, const char* value);
	void			(*pfnCvarValue2)(const edict_t* pEnt, int requestID, const char* cvarName, const char* value);
} NEW_DLL_FUNCTIONS;
typedef int	(*NEW_DLL_FUNCTIONS_FN)(NEW_DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion);

// Pointers will be null if the game DLL doesn't support this API.
extern NEW_DLL_FUNCTIONS	gNewDLLFunctions;

typedef int	(*APIFUNCTION)(DLL_FUNCTIONS* pFunctionTable, int interfaceVersion);
typedef int	(*APIFUNCTION2)(DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion);

typedef struct
{
	float		time;
	float		frametime;
	float		force_retouch;
	string_t	mapname;
	string_t	startspot;
	float		deathmatch;
	float		coop;
	float		teamplay;
	float		serverflags;
	float		found_secrets;
	vec3_t		v_forward;
	vec3_t		v_up;
	vec3_t		v_right;
	float		trace_allsolid;
	float		trace_startsolid;
	float		trace_fraction;
	vec3_t		trace_endpos;
	vec3_t		trace_plane_normal;
	float		trace_plane_dist;
	edict_t* trace_ent;
	float		trace_inopen;
	float		trace_inwater;
	int			trace_hitgroup;
	int			trace_flags;
	int			msg_entity;
	int			cdAudioTrack;
	int			maxClients;
	int			maxEntities;
	const char* pStringBase;

	void* pSaveData;
	vec3_t		vecLandmarkOffset;
} globalvars_t;
