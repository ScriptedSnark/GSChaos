#include "includes.h"

bool g_bDisableChaosUI;

//-----------------------------------------------------------------------------
// Initialize ImGui by creating context
//-----------------------------------------------------------------------------
void CImGuiManager::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
}

//-----------------------------------------------------------------------------
// Initialize OpenGL2/SDL2 backends of ImGui
//-----------------------------------------------------------------------------
void CImGuiManager::InitBackends(void* hwnd)
{
	ImGui_ImplOpenGL2_Init();
	ImGui_ImplWin32_Init(hwnd);

	// Do other things...
}

//-----------------------------------------------------------------------------
// Draw ImGui elements
//-----------------------------------------------------------------------------
void CImGuiManager::Draw()
{
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplOpenGL2_NewFrame();
	ImGui::NewFrame();

	// Here you draw...
	// -------------------------

	if (!g_bDisableChaosUI)
		gChaos.Draw();
	//ImGui::ShowDemoWindow();

	// -------------------------

	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}