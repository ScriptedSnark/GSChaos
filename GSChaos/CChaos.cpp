//TWITCH
#include "twitch/twitch.h"
#include "includes.h"

Twitch* twitch = 0;
std::thread twitch_thread;

cvar_t* chaos_effectname_ypos;
cvar_t* chaos_dmca_safe;
cvar_t* chaos_show_voting;
cvar_t* chaos_timer;
cvar_t* chaos_draw_as_overlay;

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

	if (sv->state != ss_active)
		return;

	gChaos.ActivateChaosFeature(atoi(pEngfuncs->Cmd_Argv(1)));
}

void ResetChaos()
{
	gChaos.Reset();
}

void PrintChaosVersion()
{
	gChaos.PrintVersion();
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

	m_lpRandomDevice = new CTrustedRandom();
	m_lpRandomDevice->FeedRandWithTime(time(NULL));
	m_lpRandomDevice->GenerateNewSeedTable();

	pEngfuncs->pfnAddCommand("chaos_version", PrintChaosVersion);
	pEngfuncs->pfnAddCommand("chaos_reset", ResetChaos);
	pEngfuncs->pfnAddCommand("chaos_activate", ActivateChaosFeatureW);

	chaos_effectname_ypos = pEngfuncs->pfnRegisterVariable("chaos_effectname_ypos", "0.0", 0);
	chaos_dmca_safe = pEngfuncs->pfnRegisterVariable("chaos_dmca_safe", "1", 0);
	chaos_show_voting = pEngfuncs->pfnRegisterVariable("chaos_show_voting", "0", 0);
	chaos_timer = pEngfuncs->pfnRegisterVariable("chaos_timer", "30.0", 0);
	chaos_draw_as_overlay = pEngfuncs->pfnRegisterVariable("chaos_draw_as_overlay", "0", 0);

	for (int i = 0; i < 3; i++)
	{
		m_aiEffectsForVoting[i] = GetRandomEffect(0, gChaosFeatures.size() - 1);
	}

	// Init Twitch integration (thanks to Half-Payne for this)
	if (!twitch)
	{
		twitch = new Twitch();
		twitch->OnConnected = [this] {
			printf("Connected to Twitch.\n");
			twitch->SendChatMessage("GSChaos: connected!");
			m_bTwitchVoting = true;
			Reset();
			InitVotingSystem();
			};
		twitch->OnDisconnected = [this] {
			printf("Disconnected from Twitch.\n");
			m_bTwitchVoting = false;
			};
		twitch->OnError = [this](int errorCode, const std::string& error) {
			printf("Twitch error. Code: %i | Error: %s\n", errorCode, error.c_str());
			};
		twitch->OnMessage = [this](const std::string& user, const std::string& msg) {
			Vote(user, msg);
			};

		if (!LoadTwitchSettings())
			return;

		twitch_thread = twitch->Connect(m_sUserName, m_oAuth);
		twitch_thread.detach();

		// just in case
		m_sUserName.clear();
		m_oAuth.clear();
	}
}

bool CChaos::LoadTwitchSettings()
{
	std::ifstream file(CHAOS_TWITCH_SETTINGS_FILE);
	if (!file.is_open()) {
		printf("Failed to open file: " CHAOS_TWITCH_SETTINGS_FILE "\n");
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string key, value;

		if (std::getline(iss, key, '='))
		{
			key.erase(key.find_last_not_of(" \t\r\n") + 1);

			if (!key.empty() && std::getline(iss >> std::ws, value))
			{
				value.erase(0, value.find_first_not_of(" \t\r\n"));
				value.erase(value.find_last_not_of(" \t\r\n") + 1);

				if (key == "oauth")
					m_oAuth = value;
				else if (key == "username")
					m_sUserName = value;
			}
		}
	}

	file.close();

	if (m_oAuth.empty() || m_sUserName.empty())
		return false;

	return true;
}

void CChaos::InitVotingSystem()
{
	std::ofstream outFile(CHAOS_VOTING_PROGRESS_FILE, std::ofstream::trunc);

	if (!outFile)
		pEngfuncs->Con_Printf("[CHAOS] Failed to open " CHAOS_VOTING_PROGRESS_FILE " for writing!\n");
	else
		outFile.close();

	m_aiVoteValues[0] = m_aiVoteValues[1] = m_aiVoteValues[2] = 0;

	m_twitchVoters.clear();
	m_bStartedVoting = false;
}

void CChaos::Vote(const std::string& user, const std::string& msg)
{
	if (!IsVoteStarted())
		return;

	int voteValue = -1; // TODO: enum

	auto it = std::find_if(m_twitchVoters.begin(), m_twitchVoters.end(), [&](const TwitchVoter& voter) {
		return voter.userName == user;
	});

	if (it != m_twitchVoters.end())
	{
		DEBUG_PRINT("Twitch user %s has already voted.\n", user.c_str());
		return;
	}

	if (msg.size() == 1 && std::isdigit(msg[0]))
	{
		voteValue = std::stoi(msg);
		if (voteValue >= 1 && voteValue <= 3)
		{
			m_twitchVoters.push_back({ user, voteValue - 1 });
			m_aiVoteValues[voteValue - 1]++;
			DEBUG_PRINT("Twitch user %s voted for option %i\n", user.c_str(), voteValue);
		}
		else
		{
			DEBUG_PRINT("Invalid vote value: %i\n", voteValue);
		}
	}
	else {
		DEBUG_PRINT("Invalid vote message: %s\n", msg.c_str());
	}
}

int CChaos::GetWinnerEffect()
{
	int maxVotesIndex = std::max_element(std::begin(m_aiVoteValues), std::end(m_aiVoteValues)) - std::begin(m_aiVoteValues);

	DEBUG_PRINT("Winner effect: %i\n", maxVotesIndex + 1);
	DEBUG_PRINT("Effect 1: %i votes\n", m_aiVoteValues[0]);
	DEBUG_PRINT("Effect 2: %i votes\n", m_aiVoteValues[1]);
	DEBUG_PRINT("Effect 3: %i votes\n", m_aiVoteValues[2]);

	return m_aiEffectsForVoting[maxVotesIndex];
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
	RegisterChaosFeature<CFeatureNothing>();
	RegisterChaosFeature<CFeatureDarkness>();
	RegisterChaosFeature<CFeatureTotem>();
	RegisterChaosFeature<CFeatureForgotCSS>();
	RegisterChaosFeature<CFeatureHighGravity>();
	RegisterChaosFeature<CFeatureGodMode>();
	RegisterChaosFeature<CFeatureGlobalGodMode>();
	RegisterChaosFeature<CFeatureExplosion>();
	RegisterChaosFeature<CFeatureIchthyosaur>();
	RegisterChaosFeature<CFeatureGiveRandomWeapon>();
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
	RegisterChaosFeature<CFeatureUpsideDown>();
	RegisterChaosFeature<CFeatureNPCExplode>();
	RegisterChaosFeature<CFeatureJeepy>();
	RegisterChaosFeature<CFeatureGravityField>();
	RegisterChaosFeature<CFeatureIceSkating>();
	RegisterChaosFeature<CFeatureInvertVelocity>();
	RegisterChaosFeature<CFeatureNeedForSpeed>();
	RegisterChaosFeature<CFeatureMakeItBunDem>(); // DMCA
	RegisterChaosFeature<CFeatureBikiniBottom>();
	RegisterChaosFeature<CFeatureX10Gravity>();
	RegisterChaosFeature<CFeatureOverwriteQuicksave>();
	RegisterChaosFeature<CFeatureStop>();
	RegisterChaosFeature<CFeatureNoclip>();
	RegisterChaosFeature<CFeatureGiveHealth>();
	RegisterChaosFeature<CFeatureHL2Movement>();
	RegisterChaosFeature<CFeatureGiveArmor>();
	RegisterChaosFeature<CFeatureAmIDead>();
	RegisterChaosFeature<CFeatureNodeGraphRebuilding>();
	RegisterChaosFeature<CFeatureExtremeGrieferShephard>();
	RegisterChaosFeature<CFeatureInsaneStepsize>();
	RegisterChaosFeature<CFeatureDeleteRandomEntity>();
	RegisterChaosFeature<CFeatureNuke>();
	RegisterChaosFeature<CFeaturePlusDuck>();
	RegisterChaosFeature<CFeatureMonsterWorldspawn>();
	RegisterChaosFeature<CFeatureWorldHallucination>();
	RegisterChaosFeature<CFeatureGiveOneHP>();
	RegisterChaosFeature<CFeatureTakeOneHP>();
	RegisterChaosFeature<CFeatureScientistMadness>();
	RegisterChaosFeature<CFeatureMLGAudio>();
	RegisterChaosFeature<CFeatureNoHUD>();
	RegisterChaosFeature<CFeatureQuakePro>();
	RegisterChaosFeature<CFeatureNegativeAccelerate>();
	RegisterChaosFeature<CFeatureSqueakShephard>();
	RegisterChaosFeature<CFeatureSqueakShephards>();
	RegisterChaosFeature<CFeatureBoost>();
	RegisterChaosFeature<CFeatureNotarget>();

	if (!g_bEncrypted && !g_bPreSteamPipe)
		RegisterChaosFeature<CFeatureSpawnFastrun>();

	RegisterChaosFeature<CFeatureNice>();
	RegisterChaosFeature<CFeatureHalfGravity>();
	RegisterChaosFeature<CFeatureRollin>();
	RegisterChaosFeature<CFeatureHigh>();
	RegisterChaosFeature<CFeatureShake>();
	RegisterChaosFeature<CFeatureSlap>();
	RegisterChaosFeature<CFeaturePlayAG>();
	RegisterChaosFeature<CFeatureSwapHealth>();
	RegisterChaosFeature<CFeatureTeleportToRandomNPC>();
	RegisterChaosFeature<CFeatureShuffleEntitiesPositions>();
	RegisterChaosFeature<CFeatureWideNPCs>();
	RegisterChaosFeature<CFeatureUltraWideNPCs>();
	RegisterChaosFeature<CFeatureTinyNPCs>();
	RegisterChaosFeature<CFeaturePaperNPCs>();
	RegisterChaosFeature<CFeatureGiveOneArmor>();
	RegisterChaosFeature<CFeatureReplaceModelsWithPlayer>();
	RegisterChaosFeature<CFeatureHorrorAudio>();
	RegisterChaosFeature<CFeatureLowFOV>();
	RegisterChaosFeature<CFeatureDisableChaosUI>();
	RegisterChaosFeature<CFeatureRandomFog>();
	RegisterChaosFeature<CFeatureWorstBhopCap>();
	RegisterChaosFeature<CFeatureLongJump>();
	RegisterChaosFeature<CFeatureReloadAutosave>();
	RegisterChaosFeature<CFeatureExtremeGrieferJesus>();
	RegisterChaosFeature<CFeatureMegaJump>();
	RegisterChaosFeature<CFeatureSpawn5RandomEntities>();

	// must be last
	RegisterChaosFeature<CFeatureCombineEffects>();
	RegisterChaosFeature<CFeature10Effects>();

	for (CChaosFeature* i : gChaosFeatures)
	{
		i->Init();
		gChaosFeaturesNames.push_back(i->GetFeatureName());
	}

	gChaosFeatures.shrink_to_fit();
	gChaosFeaturesNames.shrink_to_fit();

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
	m_pArialBlackItalic = io.Fonts->AddFontFromMemoryCompressedTTF(arial_black_italic_compressed_data, arial_black_compressed_size, 32.f);
	io.Fonts->Build();
	m_pArborcrest = io.Fonts->AddFontFromMemoryCompressedTTF(SF_Arborcrest_compressed_data, SF_Arborcrest_compressed_size, 22.f);
	io.Fonts->Build();
	m_fontTrebuchet = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 22.f);
	io.Fonts->Build();

	DEBUG_PRINT("CChaos::LoadFonts -> Adding Trebuchet MS...\nPath: %s\n", fontPath.c_str());
}

void CChaos::VoteThink()
{
	if (!twitch)
		return;

	m_bTwitchVoting = twitch->status == TWITCH_CONNECTED ? true : false;

	if (!m_bTwitchVoting)
		return;

	if (m_bStartedVoting)
	{
		static double timeToWrite = GetGlobalTime() + CHAOS_VOTING_PROGRESS_UPDATE_TIME;
		if (timeToWrite < GetGlobalTime())
		{
			WriteVotingProgress();
			timeToWrite = GetGlobalTime() + CHAOS_VOTING_PROGRESS_UPDATE_TIME;
		}
		
		return;
	}

	if (m_flTime > (m_flChaosTime / 3.0))
	{
		StartVoting();
	}
}

void CChaos::WriteVotingProgress()
{
	std::ofstream outFile(CHAOS_VOTING_PROGRESS_FILE, std::ofstream::trunc);
	 
	if (!outFile)
	{
		pEngfuncs->Con_Printf("[CHAOS] Failed to open " CHAOS_VOTING_PROGRESS_FILE " for writing!\n");
		return;
	}

	int totalVotes = 0;
	for (int i = 0; i < 3; i++)
	{
		totalVotes += m_aiVoteValues[i];
	}

	for (int i = 0; i < 3; i++)
	{
		float percent;

		if (totalVotes == 0)
			percent = 0.0f;
		else
			percent = (float)m_aiVoteValues[i] / (float)totalVotes * 100.f;

		outFile << "(" << i + 1 << ") " << gChaosFeaturesNames[m_aiEffectsForVoting[i]] << " | " << m_aiVoteValues[i] << " (" << (int)percent << "%)" << std::endl;
	}

	outFile << "Total Votes: " << totalVotes << std::endl;

	outFile.close();
}

void CChaos::StartVoting()
{
	if (!m_bTwitchVoting)
		return;

	InitVotingSystem();

	twitch->SendChatMessage("Start voting!");

	DEBUG_PRINT("Start voting!\n");
	DEBUG_PRINT("================\n");
	DEBUG_PRINT("Effect 1: %s\n", gChaosFeaturesNames[m_aiEffectsForVoting[0]]);
	DEBUG_PRINT("Effect 2: %s\n", gChaosFeaturesNames[m_aiEffectsForVoting[1]]);
	DEBUG_PRINT("Effect 3: %s\n", gChaosFeaturesNames[m_aiEffectsForVoting[2]]);
	DEBUG_PRINT("================\n");

	m_bStartedVoting = true;
}

void CChaos::Reset()
{
	if (m_pCurrentFeature)
		m_pCurrentFeature->DeactivateFeature();

	m_pCurrentFeature = nullptr;

	g_bDespawnExShephard = true;
	g_bDespawnJesus = true;

	auto currentTime = std::chrono::high_resolution_clock::now() - m_pauseOffset;
	m_startTime = currentTime;

	m_pauseStartTime = std::chrono::high_resolution_clock::now();

	if (chaos_timer && chaos_timer->value > 15.0f)
		m_flChaosTime = m_bTwitchVoting ? (double)chaos_timer->value + CHAOS_ADDITIONAL_TIME : (double)chaos_timer->value;
	else
		m_flChaosTime = m_bTwitchVoting ? CHAOS_ACTIVATE_TIMER + CHAOS_ADDITIONAL_TIME : CHAOS_ACTIVATE_TIMER;

	m_lpRandomDevice->FeedRandWithTime(time(NULL));
	m_lpRandomDevice->GenerateNewSeedTable();

	if (m_bTwitchVoting)
		InitVotingSystem();
}

void CChaos::Shutdown()
{
	if (twitch)
		delete twitch;
}

void CChaos::PrintVersion()
{
	pEngfuncs->Con_Printf("GSChaos (Chaos Mod) by ScriptedSnark\n");
	pEngfuncs->Con_Printf("============================\n");
	pEngfuncs->Con_Printf("Build date: " __TIMESTAMP__ "\n");
	pEngfuncs->Con_Printf("Effects: %i\n", (int)gChaosFeatures.size());
	pEngfuncs->Con_Printf("List:\n");

	int i = 0;
	for (const char* effect : gChaosFeaturesNames)
	{
		pEngfuncs->Con_Printf("- %s (ID: %i)\n", effect, i);
		i++;
	}

	pEngfuncs->Con_Printf("============================\n");
}

bool CChaos::IsVoteStarted()
{
	return (m_bTwitchVoting && m_bStartedVoting);
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

		ImGui::PushFont(m_fontTrebuchet);
		ImGui::TextWrapped("%.01f", (m_flChaosTime - m_flTime));
		ImGui::PopFont();

		ImGui::End();
	}

	m_chaosBarPos = ImGui::GetCursorPos();
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

		ImGui::End();
	}
}

void CChaos::DrawVoting()
{
	if (!IsVoteStarted())
		return;

	if (chaos_show_voting->value == 0)
		return;

	ImGui::SetNextWindowPos(ImVec2(2, m_chaosBarPos.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(640.f, 320.f), ImGuiCond_Always);

	if (ImGui::Begin("#VOTING", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		ImGui::PushFont(gChaos.m_fontTrebuchet);

		int totalVotes = 0;
		for (int i = 0; i < 3; i++)
		{
			totalVotes += m_aiVoteValues[i];
		}

		for (int i = 0; i < 3; i++)
		{
			float percent;

			if (totalVotes == 0)
				percent = 0.0f;
			else
				percent = (float)m_aiVoteValues[i] / (float)totalVotes * 100.f;

			ImGui::Text("(%i) %s | %i (%.02f%%)", i + 1, gChaosFeatures[m_aiEffectsForVoting[i]]->GetFeatureName(), m_aiVoteValues[i], percent);
		}

		ImGui::Text("Total Votes: %i", totalVotes);

		ImGui::PopFont();
		ImGui::End();
	}
}

void CChaos::Draw()
{
	DrawBar();
	DrawEffectList();
	DrawVoting();

	// TODO: do not draw if cl.paused is true
	for (CChaosFeature* i : gChaosFeatures)
	{
		i->Draw();
	}
}

void CChaos::ResetStates()
{
	if (!(*sv_player))
		return;

	if (sv->state == ss_dead)
		return;

	for (CChaosFeature* i : gChaosFeatures)
	{
		if (!i->IsActive())
			i->ResetStates();

		i->Restore();
	}
}

void CChaos::OnFrame(double time)
{
	static cvar_t* volume;
	if (!volume)
		volume = CVAR_GET_POINTER("volume");
	else
	{ // spaghetti
		if (volume->value > 0.0f)
			ma_engine_set_volume(&miniAudio, max(0.0f, volume->value) + 0.25f);
		else
			ma_engine_set_volume(&miniAudio, 0.0f);
	}

	m_bInGame = pEngfuncs->pfnGetLevelName()[0];

	static bool bPaused;

	bPaused = CLWrapper::GetPausedState();

	if (bPaused || !m_bInGame || sv->state != ss_active)
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

	auto realTime = std::chrono::high_resolution_clock::now();
	auto realDuration = std::chrono::duration_cast<std::chrono::duration<double>>(realTime - m_startGlobalTime);
	m_flRealTime = realDuration.count();

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

	VoteThink();

	if (m_flChaosTime && m_flChaosTime <= m_flTime)
	{
		DEBUG_PRINT("ACTIVATE NEW CHAOS FEATURE\n");
		
		// Reset timer
		auto currentTime = std::chrono::high_resolution_clock::now() - m_pauseOffset;
		m_startTime = currentTime;

		if (chaos_timer && chaos_timer->value > 15.0f)
			m_flChaosTime = m_bTwitchVoting ? (double)chaos_timer->value + CHAOS_ADDITIONAL_TIME : (double)chaos_timer->value;
		else
			m_flChaosTime = m_bTwitchVoting ? CHAOS_ACTIVATE_TIMER + CHAOS_ADDITIONAL_TIME : CHAOS_ACTIVATE_TIMER;
		
		m_iBarColor[0] = GetRandomValue(0, 255);
		m_iBarColor[1] = GetRandomValue(0, 255);
		m_iBarColor[2] = GetRandomValue(0, 255);
		
		// Before
		if (m_pCurrentFeature)
			m_pCurrentFeature->DeactivateFeature();

		// Do some setup
		ResetStates();
		
		if (!m_bTwitchVoting)
		{
			// Pick random effect
//#ifndef GS_DEBUG
			int i = GetRandomEffect(0, gChaosFeatures.size() - 1);
			CChaosFeature* randomFeature = gChaosFeatures[i];
//#else
//			CChaosFeature* randomFeature = gChaosFeatures[gChaosFeatures.size() - 1];
//#endif

			// After
			m_pCurrentFeature = randomFeature;
		}
		else
		{
			m_iWinnerEffect = GetWinnerEffect();
			m_pCurrentFeature = gChaosFeatures[m_iWinnerEffect];

			InitVotingSystem();

			for (int i = 0; i < 3; i++)
			{
				m_aiEffectsForVoting[i] = GetRandomEffect(0, gChaosFeatures.size() - 1);
			}
		}

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

int CChaos::GetRandomEffect(int min, int max)
{
	int result = m_lpRandomDevice->Rand(min, max);

	// intended for 30+ effects (not 3)
	while (result == m_aiPreviousRandomValue[0] || result == m_aiPreviousRandomValue[1] || result == m_aiPreviousRandomValue[2])
	{
		result = m_lpRandomDevice->Rand(min, max);
	}

	m_aiPreviousRandomValue[2] = m_aiPreviousRandomValue[1];
	m_aiPreviousRandomValue[1] = m_aiPreviousRandomValue[0];
	m_aiPreviousRandomValue[0] = result;
	return result;
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

double CChaos::GetChaosTime()
{
	return m_flChaosTime;
}

double CChaos::GetGlobalTime()
{
	return m_flGlobalTime;
}

double CChaos::GetRealTime()
{
	return m_flRealTime;
}

int CChaos::GetFrameCount() // did it only for GTA 3 HUD effect so flickering depends on FPS
{
	return m_iFrameCount;
}

bool CChaos::IsReady()
{
	return m_bInitialized && m_bInGame;
}