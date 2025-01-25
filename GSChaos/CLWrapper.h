/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CLWrapper.h 
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CLWRAPPER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CLWrapper.h
#else //CLWRAPPER_H_RECURSE_GUARD

#define CLWRAPPER_H_RECURSE_GUARD

#ifndef CLWRAPPER_H_GUARD
#define CLWRAPPER_H_GUARD
#pragma once

#ifdef __cplusplus

namespace CLWrapper
{
	model_t* GetWorldModel();
	event_t* GetEventPrecache();
	qboolean GetPausedState();
	const char* GetLevelName();
	int* GetStats();
	cl_entity_t* GetViewent();
}

#else //!__cplusplus
#error C++ compiler required to compile CLWrapper.h
#endif //__cplusplus

#endif //CLWRAPPER_H_GUARD

#undef CLWRAPPER_H_RECURSE_GUARD
#endif //CLWRAPPER_H_RECURSE_GUARD