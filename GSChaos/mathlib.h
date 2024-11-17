#ifdef MATHLIB_H_RECURSE_GUARD
#error Recursive header files inclusion detected in mathlib.h
#else //MATHLIB_H_RECURSE_GUARD

#define MATHLIB_H_RECURSE_GUARD

#ifndef MATHLIB_H_GUARD
#define MATHLIB_H_GUARD
#pragma once

#ifdef __cplusplus

#undef vec3_t

typedef float vec_t;
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];	// x,y,z,w
typedef vec_t vec5_t[5];

typedef short vec_s_t;
typedef vec_s_t vec3s_t[3];
typedef vec_s_t vec4s_t[4];	// x,y,z,w

typedef vec_s_t vec5s_t[5];

inline void VectorCopy(float* in, float* out)
{
	out[0] = in[0];
	out[1] = in[1];
	out[2] = in[2];
}

inline void VectorSub(float* in, float* out)
{
	out[0] -= in[0];
	out[1] -= in[1];
	out[2] -= in[2];
}

inline void VectorAdd(float* in, float* out)
{
	out[0] += in[0];
	out[1] += in[1];
	out[2] += in[2];
}

// Taken from pm_shared / pm_math.c 
inline float anglemod(float a)
{
	a = (360.0 / 65536) * ((int)(a * (65536 / 360.0)) & 65535);
	return a;
}

#else //!__cplusplus
#error C++ compiler required to compile mathlib.h
#endif //__cplusplus

#endif //MATHLIB_H_GUARD

#undef MATHLIB_H_RECURSE_GUARD
#endif //MATHLIB_H_RECURSE_GUARD