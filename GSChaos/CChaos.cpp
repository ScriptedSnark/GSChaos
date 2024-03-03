#include "includes.h"

cvar_t* chaos_effectname_ypos;

void ActivateChaosFeatureW()
{
	if (pEngfuncs->Cmd_Argc() <= 1)
	{
		pEngfuncs->Con_Printf("usage:  chaos_feature <id>\n");
		return;
	}

	if (!CVAR_GET_FLOAT("sv_cheats")) // need to check on server-part, not client...
		return;

	if (atoi(pEngfuncs->Cmd_Argv(1)) < 0 || (atoi(pEngfuncs->Cmd_Argv(1)) > int(gChaosFeatures.size() - 1)))
		return;

	gChaos.ActivateChaosFeature(atoi(pEngfuncs->Cmd_Argv(1)));
}

void CChaos::Init()
{
	DEBUG_PRINT("CChaos::Init\n");
	m_startTime = std::chrono::high_resolution_clock::now();

	m_flChaosTime = m_flTime + CHAOS_ACTIVATE_TIMER;
	m_bInitialized = true;

	m_iBarColor[0] = 255; // default
	m_iBarColor[1] = 180; // half-life
	m_iBarColor[2] = 30;  // hud color

	InitDynamicPrecache();
	FeatureInit();

	pEngfuncs->pfnAddCommand("chaos_activate", ActivateChaosFeatureW);

	chaos_effectname_ypos = pEngfuncs->pfnRegisterVariable("chaos_effectname_ypos", "0.0", 0);
}

void CChaos::FeatureInit()
{
	RegisterChaosFeature<CFeatureNewGame>();
	RegisterChaosFeature<CFeatureAudioCorrupt>();
	RegisterChaosFeature<CFeatureSet1HP>();
	RegisterChaosFeature<CFeatureFly>();
	RegisterChaosFeature<CFeatureRemoveArmor>();
	RegisterChaosFeature<CFeatureZeroGravity>();
	RegisterChaosFeature<CFeatureInvisibleEntities>();
	RegisterChaosFeature<CFeatureOhio>();
	RegisterChaosFeature<CFeatureFakeCrash>();
	RegisterChaosFeature<CFeatureDarkness>();
	RegisterChaosFeature<CFeatureTotem>();
	RegisterChaosFeature<CFeatureForgotCSS>();
	RegisterChaosFeature<CFeatureHighGravity>();
	RegisterChaosFeature<CFeatureGodMode>();
	RegisterChaosFeature<CFeatureGlobalGodMode>();
	RegisterChaosFeature<CFeatureExplosion>();
	RegisterChaosFeature<CFeatureIchthyosaur>();
	RegisterChaosFeature<CFeatureGiveGauss>();
	RegisterChaosFeature<CFeatureGruntAmbush>();
	RegisterChaosFeature<CFeatureGTA3HUD>();
	RegisterChaosFeature<CFeatureWeaponStrip>();
	RegisterChaosFeature<CFeatureGrieferShephard>();
	RegisterChaosFeature<CFeatureEntitySpin>();
	RegisterChaosFeature<CFeatureGTA2Camera>();
	RegisterChaosFeature<CFeatureOnePercentDeath>();
	RegisterChaosFeature<CFeatureSpawnRandomEntity>();
	RegisterChaosFeature<CFeatureSleepy>();
	RegisterChaosFeature<CFeature20FPS>();
	RegisterChaosFeature<CFeatureBSPDementia>();
	RegisterChaosFeature<CFeatureHEVMadness>();
	RegisterChaosFeature<CFeatureNegativeStepsize>();
	RegisterChaosFeature<CFeatureLobotomy>();

	RegisterChaosFeature<CFeatureCombineEffects>(); // must be last!!!

	for (CChaosFeature* i : gChaosFeatures)
	{
		i->Init();
	}

	gChaosFeatures.shrink_to_fit();

	DEBUG_PRINT("CChaos::FeatureInit -> %i registered features.\n", gChaosFeatures.size());
}

void CChaos::LoadFonts()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGuiStyle& style = ImGui::GetStyle();
	style.AntiAliasedLines = false;
	style.AntiAliasedFill = false;
	style.AntiAliasedLinesUseTex = false;

	std::string fontPath;
	fontPath = getenv("SystemRoot");
	fontPath += "\\Fonts\\trebucbd.ttf";

	m_pPricedown = io.Fonts->AddFontFromMemoryCompressedTTF(pricedown_compressed_data, pricedown_compressed_size, 48.f);
	io.Fonts->Build();
	m_pArialBlack = io.Fonts->AddFontFromMemoryCompressedTTF(arial_black_compressed_data, arial_black_compressed_size, 24.f);
	io.Fonts->Build();
	m_fontTrebuchet = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 22.f);
	io.Fonts->Build();

	DEBUG_PRINT("CChaos::LoadFonts -> Adding Trebuchet MS...\nPath: %s\n", fontPath.c_str());
}

void CChaos::DrawBar()
{
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x + 5.f, 30), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2(-5.f, 0.f));

	if (ImGui::Begin("#BAR", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float progress = (float)m_flTime / (float)m_flChaosTime;
		float bar_x = ImGui::GetIO().DisplaySize.x * progress;

		//ImGui::Text("m_flTime: %.0f | m_flChaosTime: %.0f | progress: %.3f | bar_x: %.3f", m_flTime, m_flChaosTime, progress, bar_x);
		window->DrawList->AddRectFilled(ImVec2(0.f, 0.f), ImVec2(bar_x, 30.f), ImGui::GetColorU32(ImVec4(m_iBarColor[0] / 255.f, m_iBarColor[1] / 255.f, m_iBarColor[2] / 255.f, 255 / 255.f)));
	}

	ImGui::End();
}

void CChaos::DrawEffectList()
{
	if (!m_pCurrentFeature)
		return;

	float posY = ImGui::GetIO().DisplaySize.y / 2.f;
	if (chaos_effectname_ypos && chaos_effectname_ypos->value > 1)
		posY = chaos_effectname_ypos->value;

	ImGui::SetNextWindowSize(ImVec2(0.f, 0.f));
	ImGui::SetNextWindowPos(ImVec2(0.f, posY), ImGuiCond_Always);

	if (ImGui::Begin("#EFFECTS", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings))
	{
		if (m_fontTrebuchet)
			ImGui::PushFont(m_fontTrebuchet);

		ImVec2 textPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos(ImVec2(textPos.x + 2, textPos.y + 2));
		ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "- %s", m_pCurrentFeature->GetFeatureName());
		ImGui::SetCursorPos(textPos);
		ImGui::TextColored(ImVec4(1.f, 0.627f, 0.117f, 1.f), "- %s", m_pCurrentFeature->GetFeatureName());

		if (m_fontTrebuchet)
			ImGui::PopFont();
	}
}

void CChaos::Draw()
{
	DrawBar();
	DrawEffectList();

	// TODO: do not draw if cl.paused is true
	for (CChaosFeature* i : gChaosFeatures)
	{
		i->Draw();
	}
}

void CChaos::OnFrame(double time)
{
	m_bInGame = pEngfuncs->pfnGetLevelName()[0];

	static bool bPaused;

	if (!g_bHL25)
		bPaused = cl->paused;
	else
		bPaused = cl_hl25->paused;

	if (bPaused || !m_bInGame)
	{
		if (!m_bPaused)
		{
			m_pauseStartTime = std::chrono::high_resolution_clock::now();
			m_bPaused = true;
		}
		return;
	}
	else
	{
		if (m_bPaused)
		{
			auto pauseEndTime = std::chrono::high_resolution_clock::now();
			auto pauseDuration = std::chrono::duration_cast<std::chrono::duration<double>>(pauseEndTime - m_pauseStartTime);
			m_pauseOffset += pauseDuration;
			m_bPaused = false;
		}
	}

	auto currentTime = std::chrono::high_resolution_clock::now() - m_pauseOffset;
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_startTime);
	auto globalDuration = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_startGlobalTime);

	m_flTime = duration.count();
	m_flGlobalTime = globalDuration.count();

	if (m_iFrameCount < 60) // smh
		m_iFrameCount++;
	else
		m_iFrameCount = 0;

	for (CChaosFeature* i : gChaosFeatures)
	{
		i->OnFrame(m_flTime);
	}

	if (m_flChaosTime && m_flChaosTime <= m_flTime)
	{
		DEBUG_PRINT("ACTIVATE NEW CHAOS FEATURE\n");
		
		// Reset timer
		auto currentTime = std::chrono::high_resolution_clock::now() - m_pauseOffset;
		m_startTime = currentTime;
		m_flChaosTime = CHAOS_ACTIVATE_TIMER;
		
		m_iBarColor[0] = GetRandomValue(0, 255);
		m_iBarColor[1] = GetRandomValue(0, 255);
		m_iBarColor[2] = GetRandomValue(0, 255);
		
		// Before
		if (m_pCurrentFeature)
			m_pCurrentFeature->DeactivateFeature();

		// Do some setup (?)
		(*sv_player)->v.flags &= ~FL_GODMODE;

		if ((*sv_player)->v.gravity <= 0.1f)
			(*sv_player)->v.gravity = 1.0f;

		// Pick random effect
#ifndef GS_DEBUG
		int i = GetRandomValue(0, gChaosFeatures.size() - 1);
		CChaosFeature* randomFeature = gChaosFeatures[i];
#else
		CChaosFeature* randomFeature = gChaosFeatures[gChaosFeatures.size() - 1];
#endif

		// After
		m_pCurrentFeature = randomFeature;
		m_pCurrentFeature->ActivateFeature();
	}
}

void CChaos::ActivateChaosFeature(int i)
{
	// Before
	if (m_pCurrentFeature)
		m_pCurrentFeature->DeactivateFeature();

	// Pick effect
	CChaosFeature* randomFeature = gChaosFeatures[i];

	// After
	m_pCurrentFeature = randomFeature;
	m_pCurrentFeature->ActivateFeature();
}

// TODO: improve random
int CChaos::GetRandomValue(int min, int max)
{
	static std::random_device randD;
	static std::mt19937 randMT(randD());

	std::uniform_int_distribution <int> range(min, max);
	return range(randMT);
}

float CChaos::GetRandomValue(float min, float max)
{
	static std::random_device randD;
	static std::mt19937 randMT(randD());

	std::uniform_real_distribution <float> range(min, max);
	return range(randMT);
}

double CChaos::GetTime()
{
	return m_flTime;
}

double CChaos::GetGlobalTime()
{
	return m_flGlobalTime;
}


int CChaos::GetFrameCount() // did it only for GTA 3 HUD effect so flickering depends on FPS
{
	return m_iFrameCount;
}

bool CChaos::IsReady()
{
	return m_bInitialized && m_bInGame;
}