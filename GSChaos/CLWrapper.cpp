#include "includes.h"

// WIP.
namespace CLWrapper
{
	model_t* GetWorldModel()
	{
		return cl_hl25 ? cl_hl25->worldmodel : cl->worldmodel;
	}

	qboolean GetPausedState()
	{
		return cl_hl25 ? cl_hl25->paused : cl->paused;
	}

	const char* GetLevelName()
	{
		return cl_hl25 ? cl_hl25->levelname : cl->levelname;
	}
}