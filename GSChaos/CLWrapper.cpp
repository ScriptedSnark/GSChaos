#include "includes.h"

// WIP.
namespace CLWrapper
{
	model_t* GetWorldModel()
	{
		return cl_hl25 ? cl_hl25->worldmodel : cl->worldmodel;
	}

	event_t* GetEventPrecache()
	{
		return cl_hl25 ? cl_hl25->event_precache : cl->event_precache;
	}

	qboolean GetPausedState()
	{
		return cl_hl25 ? cl_hl25->paused : cl->paused;
	}

	const char* GetLevelName()
	{
		return cl_hl25 ? cl_hl25->levelname : cl->levelname;
	}

	int* GetStats()
	{
		return cl_hl25 ? cl_hl25->stats : cl->stats;
	}

	cl_entity_t* GetViewent()
	{
		return cl_hl25 ? &cl_hl25->viewent : &cl->viewent;
	}
}