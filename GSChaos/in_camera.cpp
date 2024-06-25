

#include "includes.h"

#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorCopy(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}

typedef void (*_CAM_Think)(void);
typedef void (*_CL_CameraOffset)(float* ofs);
typedef int (*_CL_IsThirdPerson)();

_CAM_Think ORIG_CAM_Think;
_CL_CameraOffset ORIG_CL_CameraOffset;
_CL_IsThirdPerson ORIG_CL_IsThirdPerson;

void HOOKED_CL_CameraOffset(float* ofs);
int HOOKED_CL_IsThirdPerson(void);

//-------------------------------------------------- Constants

#define CAM_DIST_DELTA 1.0
#define CAM_ANGLE_DELTA 2.5
#define CAM_ANGLE_SPEED 2.5
#define CAM_MIN_DIST 30.0
#define CAM_ANGLE_MOVE .5
#define MAX_ANGLE_DIFF 10.0
#define PITCH_MAX 90.0
#define PITCH_MIN 0
#define YAW_MAX  135.0
#define YAW_MIN	 -135.0
#define PITCH 0
#define YAW 1
#define ROLL 2

enum ECAM_Command
{
	CAM_COMMAND_NONE = 0,
	CAM_COMMAND_TOTHIRDPERSON = 1,
	CAM_COMMAND_TOFIRSTPERSON = 2
};

//-------------------------------------------------- Global Variables

cvar_t* cam_command;
cvar_t* cam_snapto;
cvar_t* cam_idealyaw;
cvar_t* cam_idealpitch;
cvar_t* cam_idealdist;
cvar_t* cam_contain;

cvar_t* c_maxpitch;
cvar_t* c_minpitch;
cvar_t* c_maxyaw;
cvar_t* c_minyaw;
cvar_t* c_maxdistance;
cvar_t* c_mindistance;

cvar_t* sensitivity;

// pitch, yaw, dist
Vector cam_ofs;


// In third person
int cam_thirdperson;
int cam_mousemove; //true if we are moving the cam with the mouse, False if not
int iMouseInUse = 0;
int cam_distancemove;
extern int mouse_x, mouse_y;  //used to determine what the current x and y values are
int cam_old_mouse_x, cam_old_mouse_y; //holds the last ticks mouse movement
POINT		cam_mouse;
//-------------------------------------------------- Local Variables


//-------------------------------------------------- Prototypes

void CAM_ToThirdPerson(void);
void CAM_ToFirstPerson(void);
void CAM_StartDistance(void);
void CAM_EndDistance(void);


//-------------------------------------------------- Local Functions

float MoveToward(float cur, float goal, float maxspeed)
{
	if (cur != goal)
	{
		if (abs(cur - goal) > 180.0)
		{
			if (cur < goal)
				cur += 360.0;
			else
				cur -= 360.0;
		}

		if (cur < goal)
		{
			if (cur < goal - 1.0)
				cur += (goal - cur) / 4.0;
			else
				cur = goal;
		}
		else
		{
			if (cur > goal + 1.0)
				cur -= (cur - goal) / 4.0;
			else
				cur = goal;
		}
	}


	// bring cur back into range
	if (cur < 0)
		cur += 360.0;
	else if (cur >= 360)
		cur -= 360;

	return cur;
}


//-------------------------------------------------- Gobal Functions

typedef struct
{
	Vector		boxmins, boxmaxs;// enclose the test object along entire move
	float* mins, * maxs;	// size of the moving object
	Vector		mins2, maxs2;	// size when clipping against mosnters
	float* start, * end;
	trace_t		trace;
	int			type;
	edict_t* passedict;
	qboolean	monsterclip;
} moveclip_t;

void HOOKED_CAM_Think(void)
{
	Vector origin;
	Vector ext, pnt, camForward, camRight, camUp;
	moveclip_t	clip;
	float dist;
	Vector camAngles;
	float flSensitivity;
#ifdef LATER
	int i;
#endif
	Vector viewangles;

	switch ((int)cam_command->value)
	{
	case CAM_COMMAND_TOTHIRDPERSON:
		CAM_ToThirdPerson();
		break;

	case CAM_COMMAND_TOFIRSTPERSON:
		CAM_ToFirstPerson();
		break;

	case CAM_COMMAND_NONE:
	default:
		break;
	}

	if (!cam_thirdperson)
		return;

#ifdef LATER
	if (cam_contain->value)
	{
		pEngfuncs->GetClientOrigin(origin);
		ext[0] = ext[1] = ext[2] = 0.0;
	}
#endif

	camAngles[PITCH] = cam_idealpitch->value;
	camAngles[YAW] = cam_idealyaw->value;
	dist = cam_idealdist->value;
	//
	//movement of the camera with the mouse
	//
	if (cam_mousemove)
	{
		//get windows cursor position
		GetCursorPos(&cam_mouse);
		//check for X delta values and adjust accordingly
		//eventually adjust YAW based on amount of movement
	  //don't do any movement of the cam using YAW/PITCH if we are zooming in/out the camera	
		if (!cam_distancemove)
		{

			//keep the camera within certain limits around the player (ie avoid certain bad viewing angles)  
			if (cam_mouse.x > pEngfuncs->GetWindowCenterX())
			{
				//if ((camAngles[YAW]>=225.0)||(camAngles[YAW]<135.0))
				if (camAngles[YAW] < c_maxyaw->value)
				{
					camAngles[YAW] += (CAM_ANGLE_MOVE) * ((cam_mouse.x - pEngfuncs->GetWindowCenterX()) / 2);
				}
				if (camAngles[YAW] > c_maxyaw->value)
				{

					camAngles[YAW] = c_maxyaw->value;
				}
			}
			else if (cam_mouse.x < pEngfuncs->GetWindowCenterX())
			{
				//if ((camAngles[YAW]<=135.0)||(camAngles[YAW]>225.0))
				if (camAngles[YAW] > c_minyaw->value)
				{
					camAngles[YAW] -= (CAM_ANGLE_MOVE) * ((pEngfuncs->GetWindowCenterX() - cam_mouse.x) / 2);

				}
				if (camAngles[YAW] < c_minyaw->value)
				{
					camAngles[YAW] = c_minyaw->value;

				}
			}

			//check for y delta values and adjust accordingly
			//eventually adjust PITCH based on amount of movement
			//also make sure camera is within bounds
			if (cam_mouse.y > pEngfuncs->GetWindowCenterY())
			{
				if (camAngles[PITCH] < c_maxpitch->value)
				{
					camAngles[PITCH] += (CAM_ANGLE_MOVE) * ((cam_mouse.y - pEngfuncs->GetWindowCenterY()) / 2);
				}
				if (camAngles[PITCH] > c_maxpitch->value)
				{
					camAngles[PITCH] = c_maxpitch->value;
				}
			}
			else if (cam_mouse.y < pEngfuncs->GetWindowCenterY())
			{
				if (camAngles[PITCH] > c_minpitch->value)
				{
					camAngles[PITCH] -= (CAM_ANGLE_MOVE) * ((pEngfuncs->GetWindowCenterY() - cam_mouse.y) / 2);
				}
				if (camAngles[PITCH] < c_minpitch->value)
				{
					camAngles[PITCH] = c_minpitch->value;
				}
			}

			//set old mouse coordinates to current mouse coordinates
			//since we are done with the mouse

			if ((flSensitivity = sensitivity->value) != 0)
			{
				cam_old_mouse_x = cam_mouse.x * flSensitivity;
				cam_old_mouse_y = cam_mouse.y * flSensitivity;
			}
			else
			{
				cam_old_mouse_x = cam_mouse.x;
				cam_old_mouse_y = cam_mouse.y;
			}
			SetCursorPos(pEngfuncs->GetWindowCenterX(), pEngfuncs->GetWindowCenterY());
		}
	}

	if (cam_distancemove)
	{
		if (cam_mouse.y > pEngfuncs->GetWindowCenterY())
		{
			if (dist < c_maxdistance->value)
			{
				dist += CAM_DIST_DELTA * ((cam_mouse.y - pEngfuncs->GetWindowCenterY()) / 2);
			}
			if (dist > c_maxdistance->value)
			{
				dist = c_maxdistance->value;
			}
		}
		else if (cam_mouse.y < pEngfuncs->GetWindowCenterY())
		{
			if (dist > c_mindistance->value)
			{
				dist -= (CAM_DIST_DELTA) * ((pEngfuncs->GetWindowCenterY() - cam_mouse.y) / 2);
			}
			if (dist < c_mindistance->value)
			{
				dist = c_mindistance->value;
			}
		}
		//set old mouse coordinates to current mouse coordinates
		//since we are done with the mouse
		cam_old_mouse_x = cam_mouse.x * sensitivity->value;
		cam_old_mouse_y = cam_mouse.y * sensitivity->value;
		SetCursorPos(pEngfuncs->GetWindowCenterX(), pEngfuncs->GetWindowCenterY());
	}
#ifdef LATER
	if (cam_contain->value)
	{
		// check new ideal
		VectorCopy(origin, pnt);
		AngleVectors(camAngles, camForward, camRight, camUp);
		for (i = 0; i < 3; i++)
			pnt[i] += -dist * camForward[i];

		// check line from r_refdef.vieworg to pnt
		memset(&clip, 0, sizeof(moveclip_t));
		clip.trace = SV_ClipMoveToEntity(sv.edicts, r_refdef.vieworg, ext, ext, pnt);
		if (clip.trace.fraction == 1.0)
		{
			// update ideal
			cam_idealpitch->value = camAngles[PITCH];
			cam_idealyaw->value = camAngles[YAW];
			cam_idealdist->value = dist;
		}
	}
	else
#endif
	{
		// update ideal
		cam_idealpitch->value = camAngles[PITCH];
		cam_idealyaw->value = camAngles[YAW];
		cam_idealdist->value = dist;
	}

	// Move towards ideal
	VectorCopy(cam_ofs, camAngles);

	pEngfuncs->GetViewAngles((float*)viewangles);

	if (cam_snapto->value)
	{
		camAngles[YAW] = cam_idealyaw->value + viewangles[YAW];
		camAngles[PITCH] = cam_idealpitch->value + viewangles[PITCH];
		camAngles[2] = cam_idealdist->value;
	}
	else
	{
		if (camAngles[YAW] - viewangles[YAW] != cam_idealyaw->value)
			camAngles[YAW] = MoveToward(camAngles[YAW], cam_idealyaw->value + viewangles[YAW], CAM_ANGLE_SPEED);

		if (camAngles[PITCH] - viewangles[PITCH] != cam_idealpitch->value)
			camAngles[PITCH] = MoveToward(camAngles[PITCH], cam_idealpitch->value + viewangles[PITCH], CAM_ANGLE_SPEED);

		if (abs(camAngles[2] - cam_idealdist->value) < 2.0)
			camAngles[2] = cam_idealdist->value;
		else
			camAngles[2] += (cam_idealdist->value - camAngles[2]) / 4.0;
	}
#ifdef LATER
	if (cam_contain->value)
	{
		// Test new position
		dist = camAngles[ROLL];
		camAngles[ROLL] = 0;

		VectorCopy(origin, pnt);
		AngleVectors(camAngles, camForward, camRight, camUp);
		for (i = 0; i < 3; i++)
			pnt[i] += -dist * camForward[i];

		// check line from r_refdef.vieworg to pnt
		memset(&clip, 0, sizeof(moveclip_t));
		ext[0] = ext[1] = ext[2] = 0.0;
		clip.trace = SV_ClipMoveToEntity(sv.edicts, r_refdef.vieworg, ext, ext, pnt);
		if (clip.trace.fraction != 1.0)
			return;
	}
#endif
	cam_ofs[0] = camAngles[0];
	cam_ofs[1] = camAngles[1];
	cam_ofs[2] = dist;
}

void CAM_ToThirdPerson(void)
{
	Vector viewangles;

	pEngfuncs->GetViewAngles((float*)viewangles);

	if (!cam_thirdperson)
	{
		cam_thirdperson = 1;

		cam_ofs[YAW] = viewangles[YAW];
		cam_ofs[PITCH] = viewangles[PITCH];
		cam_ofs[2] = CAM_MIN_DIST;
	}

	pEngfuncs->Cvar_SetValue("chaos_cam_command", 0);
}

void CAM_ToFirstPerson(void)
{
	cam_thirdperson = 0;

	pEngfuncs->Cvar_SetValue("chaos_cam_command", 0);
}

void CAM_ToggleSnapto(void)
{
	cam_snapto->value = !cam_snapto->value;
}

void CAM_Init(void)
{
	int status;
	Find(Client, CAM_Think);
	Find(Client, CL_CameraOffset);
	Find(Client, CL_IsThirdPerson);
	CreateHook(Client, CAM_Think);
	CreateHook(Client, CL_CameraOffset);
	CreateHook(Client, CL_IsThirdPerson);

	pEngfuncs->pfnAddCommand("chaos_thirdperson", CAM_ToThirdPerson);
	pEngfuncs->pfnAddCommand("chaos_firstperson", CAM_ToFirstPerson);

	cam_command = pEngfuncs->pfnRegisterVariable("chaos_cam_command", "0", 0);	 // tells camera to go to thirdperson
	cam_snapto = pEngfuncs->pfnRegisterVariable("chaos_cam_snapto", "0", 0);	 // snap to thirdperson view
	cam_idealyaw = pEngfuncs->pfnRegisterVariable("chaos_cam_idealyaw", "0", 0);	 // thirdperson yaw
	cam_idealpitch = pEngfuncs->pfnRegisterVariable("chaos_cam_idealpitch", "0", 0);	 // thirperson pitch
	cam_idealdist = pEngfuncs->pfnRegisterVariable("chaos_cam_idealdist", "64", 0);	 // thirdperson distance
	cam_contain = pEngfuncs->pfnRegisterVariable("chaos_cam_contain", "0", 0);	// contain camera to world

	c_maxpitch = pEngfuncs->pfnRegisterVariable("chaos_c_maxpitch", "90.0", 0);
	c_minpitch = pEngfuncs->pfnRegisterVariable("chaos_c_minpitch", "0.0", 0);
	c_maxyaw = pEngfuncs->pfnRegisterVariable("chaos_c_maxyaw", "135.0", 0);
	c_minyaw = pEngfuncs->pfnRegisterVariable("chaos_c_minyaw", "-135.0", 0);
	c_maxdistance = pEngfuncs->pfnRegisterVariable("chaos_c_maxdistance", "200.0", 0);
	c_mindistance = pEngfuncs->pfnRegisterVariable("chaos_c_mindistance", "30.0", 0);

	sensitivity = pEngfuncs->pfnGetCvarPointer("sensitivity");
}

void CAM_ClearStates(void)
{
	Vector viewangles;

	pEngfuncs->GetViewAngles((float*)viewangles);

	cam_thirdperson = 0;
	cam_command->value = 0;
	cam_mousemove = 0;

	cam_snapto->value = 0;
	cam_distancemove = 0;

	cam_ofs[0] = 0.0;
	cam_ofs[1] = 0.0;
	cam_ofs[2] = CAM_MIN_DIST;

	cam_idealpitch->value = viewangles[PITCH];
	cam_idealyaw->value = viewangles[YAW];
	cam_idealdist->value = CAM_MIN_DIST;
}

void CAM_StartMouseMove(void)
{
	float flSensitivity;

	//only move the cam with mouse if we are in third person.
	if (cam_thirdperson)
	{
		//set appropriate flags and initialize the old mouse position
		//variables for mouse camera movement
		if (!cam_mousemove)
		{
			cam_mousemove = 1;
			iMouseInUse = 1;
			GetCursorPos(&cam_mouse);

			if ((flSensitivity = sensitivity->value) != 0)
			{
				cam_old_mouse_x = cam_mouse.x * flSensitivity;
				cam_old_mouse_y = cam_mouse.y * flSensitivity;
			}
			else
			{
				cam_old_mouse_x = cam_mouse.x;
				cam_old_mouse_y = cam_mouse.y;
			}
		}
	}
	//we are not in 3rd person view..therefore do not allow camera movement
	else
	{
		cam_mousemove = 0;
		iMouseInUse = 0;
	}
}

//the key has been released for camera movement
//tell the engine that mouse camera movement is off
void CAM_EndMouseMove(void)
{
	cam_mousemove = 0;
	iMouseInUse = 0;
}


//----------------------------------------------------------
//routines to start the process of moving the cam in or out 
//using the mouse
//----------------------------------------------------------
void CAM_StartDistance(void)
{
	//only move the cam with mouse if we are in third person.
	if (cam_thirdperson)
	{
		//set appropriate flags and initialize the old mouse position
		//variables for mouse camera movement
		if (!cam_distancemove)
		{
			cam_distancemove = 1;
			cam_mousemove = 1;
			iMouseInUse = 1;
			GetCursorPos(&cam_mouse);
			cam_old_mouse_x = cam_mouse.x * sensitivity->value;
			cam_old_mouse_y = cam_mouse.y * sensitivity->value;
		}
	}
	//we are not in 3rd person view..therefore do not allow camera movement
	else
	{
		cam_distancemove = 0;
		cam_mousemove = 0;
		iMouseInUse = 0;
	}
}

//the key has been released for camera movement
//tell the engine that mouse camera movement is off
void CAM_EndDistance(void)
{
	cam_distancemove = 0;
	cam_mousemove = 0;
	iMouseInUse = 0;
}

void HOOKED_CL_CameraOffset(float* ofs)
{
	ORIG_CL_CameraOffset(ofs);
	VectorCopy(cam_ofs, ofs);
}

int HOOKED_CL_IsThirdPerson(void)
{
	return (cam_thirdperson ? 1 : ORIG_CL_IsThirdPerson());
}