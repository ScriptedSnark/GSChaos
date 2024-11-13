#ifdef IMGUI_MANAGER_HPP_RECURSE_GUARD
#error Recursive header files inclusion detected in imgui_manager.hpp
#else //IMGUI_MANAGER_HPP_RECURSE_GUARD

#define IMGUI_MANAGER_HPP_RECURSE_GUARD

#ifndef IMGUI_MANAGER_HPP_GUARD
#define IMGUI_MANAGER_HPP_GUARD
#pragma once

#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"

extern bool g_bDisableChaosUI;

class CImGuiManager
{
public:
	void Init();
	void InitBackends(void* hwnd);
	bool CanUseEngineResolution();
	void UpdateResolution(ImVec2& displaySize, ImVec2& frameBufferScale, ImVec2 realDisplaySize);
	void Draw();
	
	ImVec2 m_vecRealDisplaySize;
};

#endif //IMGUI_MANAGER_HPP_GUARD

#undef IMGUI_MANAGER_HPP_RECURSE_GUARD
#endif //IMGUI_MANAGER_HPP_RECURSE_GUARD