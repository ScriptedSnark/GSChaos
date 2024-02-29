#ifdef SVC_MESSAGES_H_RECURSE_GUARD
#error Recursive header files inclusion detected in svc_messages.h
#else //SVC_MESSAGES_H_RECURSE_GUARD

#define SVC_MESSAGES_H_RECURSE_GUARD

#ifndef SVC_MESSAGES_H_GUARD
#define SVC_MESSAGES_H_GUARD
#pragma once

#ifdef __cplusplus

#define SVC_BAD 				0
#define SVC_NOP					1
#define SVC_DISCONNECT			2
#define SVC_EVENT				3
#define SVC_VERSION				4
#define SVC_SETVIEW				5
#define SVC_SOUND				6
#define SVC_TIME				7
#define SVC_PRINT				8
#define SVC_STUFFTEXT			9
#define SVC_SETANGLE			10
#define SVC_SERVERINFO			11
#define SVC_LIGHTSTYLE			12
#define SVC_UPDATEUSERINFO		13
#define SVC_DELTADESCRIPTION	14
#define SVC_CLIENTDATA			15
#define SVC_STOPSOUND			16
#define SVC_PINGS				17
#define SVC_PARTICLE			18
#define SVC_DAMAGE				19
#define SVC_SPAWNSTATIC			20
#define SVC_EVENT_RELIABLE		21
#define SVC_SPAWNBASELINE		22
#define SVC_TEMPENTITY			23
#define SVC_SETPAUSE			24
#define SVC_SIGNONNUM			25
#define SVC_CENTERPRINT			26
#define SVC_KILLEDMONSTER		27
#define SVC_FOUNDSECRET			28
#define SVC_SPAWNSTATICSOUND	29
#define SVC_INTERMISSION		30
#define SVC_FINALE				31
#define SVC_CDTRACK				32
#define SVC_RESTORE				33
#define SVC_CUTSCENE			34
#define SVC_WEAPONANIM			35
#define SVC_DECALNAME			36
#define SVC_ROOMTYPE			37
#define SVC_ADDANGLE			38
#define SVC_NEWUSERMSG			39
#define SVC_PACKETENTITIES		40
#define SVC_DELTAPACKETENTITIES	41
#define SVC_CHOKE				42
#define SVC_RESOURCELIST		43
#define SVC_NEWMOVEVARS			44
#define SVC_RESOURCEREQUEST		45
#define SVC_CUSTOMIZATION		46
#define SVC_CROSSHAIRANGLE		47
#define SVC_SOUNDFADE			48
#define SVC_FILETXFERFAILED		49
#define SVC_HLTV				50
#define SVC_DIRECTOR			51
#define SVC_VOICEINIT			52
#define SVC_VOICEDATA			53
#define SVC_SENDEXTRAINFO		54
#define SVC_TIMESCALE			55
#define SVC_RESOURCELOCATION 	56
#define SVC_SENDCVARVALUE 		57
#define SVC_SENDCVARVALUE2 		58

typedef struct _UserMsg
{
	int iMsg;
	int iSize;
	char szName[16];
	_UserMsg* next;
	pfnUserMsgHook pfn;
} UserMsg;

const int MAX_CONSISTENCY_LIST = 512;

typedef struct consistency_s
{
	char* filename;
	int issound;
	int orig_index;
	int value;
	int check_type;
	float mins[3];
	float maxs[3];
} consistency_t;

typedef struct event_s
{
	unsigned short index;
	const char* filename;
	int filesize;
	const char* pszScript;
} event_t;

typedef enum server_state_e
{
	ss_dead = 0,
	ss_loading = 1,
	ss_active = 2,
} server_state_t;

typedef struct sizebuf_s
{
	const char* buffername;
	uint16 flags;
	byte* data;
	int maxsize;
	int cursize;
} sizebuf_t;

const int NUM_BASELINES = 64;
#define MAX_RESOURCE_LIST 1280

#define MAX_MODEL_INDEX_BITS 9 // sent as a short
#define MAX_MODELS (1 << MAX_MODEL_INDEX_BITS)

#define MAX_EVENTS 256

#define MAX_SOUND_INDEX_BITS 9
#define MAX_SOUNDS (1 << MAX_SOUND_INDEX_BITS)
#define MAX_SOUNDS_HASHLOOKUP_SIZE (MAX_SOUNDS * 2 - 1)

#define MAX_GENERIC_INDEX_BITS 9
#define MAX_GENERIC (1 << MAX_GENERIC_INDEX_BITS)

#define MAX_LIGHTSTYLE_INDEX_BITS 6
#define MAX_LIGHTSTYLES (1 << MAX_LIGHTSTYLE_INDEX_BITS)

const int MAX_DATAGRAM = 4000;

typedef struct extra_baselines_s
{
	int number;
	int classname[NUM_BASELINES];
	entity_state_t baseline[NUM_BASELINES];
} extra_baselines_t;

typedef struct server_s
{
	qboolean active;
	qboolean paused;
	qboolean loadgame;
	double time;
	double oldtime;
	int lastcheck;
	double lastchecktime;
	char name[64];
	char oldname[64];
	char startspot[64];
	char modelname[64];
	struct model_s* worldmodel;
	CRC32_t worldmapCRC;
	unsigned char clientdllmd5[16];
	resource_t resourcelist[MAX_RESOURCE_LIST];
	int num_resources;
	consistency_t consistency_list[MAX_CONSISTENCY_LIST];
	int num_consistency;
	const char* model_precache[MAX_MODELS];
	struct model_s* models[MAX_MODELS];
	unsigned char model_precache_flags[MAX_MODELS];
	struct event_s event_precache[MAX_EVENTS];
	const char* sound_precache[MAX_SOUNDS];
	short int sound_precache_hashedlookup[MAX_SOUNDS_HASHLOOKUP_SIZE];
	qboolean sound_precache_hashedlookup_built;
	const char* generic_precache[MAX_GENERIC];
	char generic_precache_names[MAX_GENERIC][64];
	int num_generic_names;
	const char* lightstyles[MAX_LIGHTSTYLES];
	int num_edicts;
	int max_edicts;
	edict_t* edicts;
	entity_state_s* baselines;
	extra_baselines_t* instance_baselines;
	server_state_t state;
	sizebuf_t datagram;
	unsigned char datagram_buf[MAX_DATAGRAM];
	sizebuf_t reliable_datagram;
	unsigned char reliable_datagram_buf[MAX_DATAGRAM];
	sizebuf_t multicast;
	unsigned char multicast_buf[1024];
	sizebuf_t spectator;
	unsigned char spectator_buf[1024];
	sizebuf_t signon;
	unsigned char signon_data[32768];
} server_t;

#define MAX_PACKET_ENTITIES 256
#define MAX_PACKET_ENTITIES_HL25 1024

struct packet_entities_t
{
	int num_entities;
	byte flags[MAX_PACKET_ENTITIES / 8];
	entity_state_s* entities;
};

struct packet_entities_HL25_t
{
	int num_entities;
	byte flags[MAX_PACKET_ENTITIES_HL25 / 8];
	entity_state_s* entities;
};

typedef struct cmd_s
{
	usercmd_t cmd;
	float senttime;
	float receivedtime;
	float frame_lerp;
	qboolean processedfuncs;
	qboolean heldback;
	int sendsize;
} cmd_t;

typedef struct event_args_s
{
	int flags;
	int entindex;
	float origin[3];
	float angles[3];
	float velocity[3];
	int ducking;
	float fparam1;
	float fparam2;
	int iparam1;
	int iparam2;
	int bparam1;
	int bparam2;
} event_args_t;


struct event_info_s
{
	unsigned short index; // 0 implies not in use

	short packet_index; // Use data from state info for entity in delta_packet .  -1 implies separate info based on event
	// parameter signature
	short entity_index; // The edict this event is associated with

	float fire_time; // if non-zero, the time when the event should be fired ( fixed up on the client )

	event_args_t args;

	// CLIENT ONLY
	int flags; // Reliable or not, etc.
};

typedef struct event_state_s event_state_t;

struct event_state_s
{
	struct event_info_s ei[64];
};

typedef struct screenfade_s
{
	float fadeSpeed;
	float fadeEnd;
	float fadeTotalEnd;
	float fadeReset;
	byte fader;
	byte fadeg;
	byte fadeb;
	byte fadealpha;
	int fadeFlags;
} screenfade_t;

typedef struct clientdata_s
{
	vec3_t origin;
	vec3_t velocity;
	int viewmodel;
	vec3_t punchangle;
	int flags;
	int waterlevel;
	int watertype;
	vec3_t view_ofs;
	float health;
	int bInDuck;
	int weapons;
	int flTimeStepSound;
	int flDuckTime;
	int flSwimTime;
	int waterjumptime;
	float maxspeed;
	float fov;
	int weaponanim;
	int m_iId;
	int ammo_shells;
	int ammo_nails;
	int ammo_cells;
	int ammo_rockets;
	float m_flNextAttack;
	int tfstate;
	int pushmsec;
	int deadflag;
	char physinfo[256];
	int iuser1;
	int iuser2;
	int iuser3;
	int iuser4;
	float fuser1;
	float fuser2;
	float fuser3;
	float fuser4;
	vec3_t vuser1;
	vec3_t vuser2;
	vec3_t vuser3;
	vec3_t vuser4;
} clientdata_t;

typedef struct weapon_data_s
{
	int m_iId;
	int m_iClip;
	float m_flNextPrimaryAttack;
	float m_flNextSecondaryAttack;
	float m_flTimeWeaponIdle;
	int m_fInReload;
	int m_fInSpecialReload;
	float m_flNextReload;
	float m_flPumpTime;
	float m_fReloadTime;
	float m_fAimedDamage;
	float m_fNextAimBonus;
	int m_fInZoom;
	int m_iWeaponState;
	int iuser1;
	int iuser2;
	int iuser3;
	int iuser4;
	float fuser1;
	float fuser2;
	float fuser3;
	float fuser4;
} weapon_data_t;

typedef struct local_state_s
{
	entity_state_t playerstate;
	clientdata_t client;
	weapon_data_t weapondata[64];
} local_state_t;

typedef struct dlight_s
{
	vec3_t origin;
	float radius;
	color24 color;
	float die;
	float decay;
	float minlight;
	int key;
	qboolean dark;
} dlight_t;

typedef struct player_info_s
{
	int userid;
	char userinfo[256];
	char name[32];
	int spectator;
	int ping;
	int packet_loss;
	char model[64];
	int topcolor;
	int bottomcolor;
	int renderframe;
	int gaitsequence;
	float gaitframe;
	float gaityaw;
	vec3_t prevgaitorigin;
	customization_t customdata;
	char hashedcdkey[16];
	uint64 m_nSteamID;
} player_info_t;

typedef struct frame_s
{
	double receivedtime;
	double latency;
	qboolean invalid;
	qboolean choked;
	entity_state_t playerstate[32];
	double time;
	clientdata_t clientdata;
	weapon_data_t weapondata[64];
	packet_entities_t packet_entities;
	unsigned short clientbytes;
	unsigned short playerinfobytes;
	unsigned short packetentitybytes;
	unsigned short tentitybytes;
	unsigned short soundbytes;
	unsigned short eventbytes;
	unsigned short usrbytes;
	unsigned short voicebytes;
	unsigned short msgbytes;

} frame_t;

typedef struct frame_HL25_s
{
	double receivedtime;
	double latency;
	qboolean invalid;
	qboolean choked;
	entity_state_t playerstate[32];
	double time;
	clientdata_t clientdata;
	weapon_data_t weapondata[64];
	packet_entities_HL25_t packet_entities;
	unsigned short clientbytes;
	unsigned short playerinfobytes;
	unsigned short packetentitybytes;
	unsigned short tentitybytes;
	unsigned short soundbytes;
	unsigned short eventbytes;
	unsigned short usrbytes;
	unsigned short voicebytes;
	unsigned short msgbytes;
} frame_HL25_t;

typedef struct client_state_s
{
	int max_edicts;
	resource_t resourcesonhand;
	resource_t resourcesneeded;
	resource_t resourcelist[MAX_RESOURCE_LIST];
	int num_resources;
	qboolean need_force_consistency_response;
	char serverinfo[512];
	int servercount;
	int validsequence;
	int parsecount;
	int parsecountmod;
	int stats[32];
	int weapons;
	usercmd_t cmd;
	Vector viewangles;
	Vector punchangle;
	Vector crosshairangle;
	Vector simorg;
	Vector simvel;
	Vector simangles;
	Vector predicted_origins[64];
	Vector prediction_error;
	float idealpitch;
	Vector viewheight;
	screenfade_t sf;
	qboolean paused;
	int onground;
	int moving;
	int waterlevel;
	int usehull;
	float maxspeed;
	int pushmsec;
	int light_level;
	int intermission;
	double mtime[2];
	double time;
	double oldtime;
	frame_t frames[64];
	cmd_t commands[64];
	local_state_t predicted_frames[64];
	int delta_sequence;
	int playernum;
	event_t event_precache[MAX_EVENTS];
	model_t* model_precache[MAX_MODELS];
	int model_precache_count;
	sfx_t* sound_precache[MAX_SOUNDS];
	consistency_t consistency_list[MAX_CONSISTENCY_LIST];
	int num_consistency;
	int highentity;
	char levelname[40];
	int maxclients;
	int gametype;
	int viewentity;
	model_t* worldmodel;
	efrag_t* free_efrags;
	int num_entities;
	int num_statics;
	cl_entity_t viewent;
	int cdtrack;
	int looptrack;
	CRC32_t serverCRC;
	unsigned char clientdllmd5[16];
	float weaponstarttime;
	int weaponsequence;
	int fPrecaching;
	dlight_t* pLight;
	player_info_t players[32];
	entity_state_t instanced_baseline[64];
	int instanced_baseline_number;
	CRC32_t mapCRC;
	event_state_t events;
	char downloadUrl[128];
} client_state_t;

typedef struct client_state_HL25_s
{
	int max_edicts;
	resource_t resourcesonhand;
	resource_t resourcesneeded;
	resource_t resourcelist[MAX_RESOURCE_LIST];
	int num_resources;
	qboolean need_force_consistency_response;
	char serverinfo[512];
	int servercount;
	int validsequence;
	int parsecount;
	int parsecountmod;
	int stats[32];
	int weapons;
	usercmd_t cmd;
	Vector viewangles;
	Vector punchangle;
	Vector crosshairangle;
	Vector simorg;
	Vector simvel;
	Vector simangles;
	Vector predicted_origins[64];
	Vector prediction_error;
	float idealpitch;
	Vector viewheight;
	screenfade_t sf;
	qboolean paused;
	int onground;
	int moving;
	int waterlevel;
	int usehull;
	float maxspeed;
	int pushmsec;
	int light_level;
	int intermission;
	double mtime[2];
	double time;
	double oldtime;
	frame_HL25_t frames[64];
	cmd_t commands[64];
	local_state_t predicted_frames[64];
	int delta_sequence;
	int playernum;
	event_t event_precache[MAX_EVENTS];
	model_t* model_precache[MAX_MODELS];
	int model_precache_count;
	sfx_t* sound_precache[MAX_SOUNDS];
	consistency_t consistency_list[MAX_CONSISTENCY_LIST];
	int num_consistency;
	int highentity;
	char levelname[40];
	int maxclients;
	int gametype;
	int viewentity;
	model_t* worldmodel;
	efrag_t* free_efrags;
	int num_entities;
	int num_statics;
	cl_entity_t viewent;
	int cdtrack;
	int looptrack;
	CRC32_t serverCRC;
	unsigned char clientdllmd5[16];
	float weaponstarttime;
	int weaponsequence;
	int fPrecaching;
	dlight_t* pLight;
	player_info_t players[32];
	entity_state_t instanced_baseline[64];
	int instanced_baseline_number;
	CRC32_t mapCRC;
	event_state_t events;
	char downloadUrl[128];
} client_state_HL25_t;


#else //!__cplusplus
#error C++ compiler required to compile svc_messages.h
#endif //__cplusplus

#endif //SVC_MESSAGES_H_GUARD

#undef SVC_MESSAGES_H_RECURSE_GUARD
#endif //SVC_MESSAGES_H_RECURSE_GUARD