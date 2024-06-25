#ifdef IN_CAMERA_H_RECURSE_GUARD
#error Recursive header files inclusion detected in in_camera.h
#else //IN_CAMERA_H_RECURSE_GUARD

#define IN_CAMERA_H_RECURSE_GUARD

#ifndef IN_CAMERA_H_GUARD
#define IN_CAMERA_H_GUARD
#pragma once

#ifdef __cplusplus

extern cvar_t* cam_command;
extern cvar_t* cam_snapto;
extern cvar_t* cam_idealyaw;
extern cvar_t* cam_idealpitch;
extern cvar_t* cam_idealdist;
extern cvar_t* cam_contain;

extern cvar_t* c_maxpitch;
extern cvar_t* c_minpitch;
extern cvar_t* c_maxyaw;
extern cvar_t* c_minyaw;
extern cvar_t* c_maxdistance;
extern cvar_t* c_mindistance;

#else //!__cplusplus
#error C++ compiler required to compile in_camera.h
#endif //__cplusplus

#endif //IN_CAMERA_H_GUARD

#undef IN_CAMERA_H_RECURSE_GUARD
#endif //IN_CAMERA_H_RECURSE_GUARD