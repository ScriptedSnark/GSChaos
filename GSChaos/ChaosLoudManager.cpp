#include "includes.h"

namespace ChaosLoud
{
	SoLoud::Wav g_wBank[SOUNDBANK_SIZE];
	float g_flVolume = 0.0f;
	cvar_t* volume, *chaos_volume_multiplier;

	void LoadSounds()
	{
		if (chaos_volume_multiplier == nullptr)
		{
			chaos_volume_multiplier = pEngfuncs->pfnRegisterVariable("chaos_volume_multiplier", "3", 0);
		}

		g_wBank[MUSIC_JESUS].load("chaos/egj.mp3");
		g_wBank[MUSIC_OPFOR01].load("chaos/opfor01.mp3");
		g_wBank[SND_SLAP].load("chaos/slap.mp3");
		g_wBank[SND_GTA3_WPN_PICKUP].load("chaos/hud/wpn_pickup.wav");
		g_wBank[SND_GTA3_ITEM_PICKUP].load("chaos/hud/item_pickup.wav");
		g_wBank[SND_GTA3_NOTIFY].load("chaos/hud/notify.wav");
		g_wBank[SND_GTAVC_WPN_PICKUP].load("chaos/vc_hud/wpn_pickup.wav");
		g_wBank[SND_GTAVC_ITEM_PICKUP].load("chaos/vc_hud/item_pickup.wav");
		g_wBank[SND_GTAVC_NOTIFY].load("chaos/vc_hud/notify.wav");
		g_wBank[SND_LASAGNA].load("chaos/lasagna.mp3");
		g_wBank[SND_LOBOTOMY].load("chaos/lobotomy.wav");
		g_wBank[SND_TOTEM].load("chaos/totem.wav");
		g_wBank[SND_RESPECT].load("chaos/sci_respect.wav");
		g_wBank[SND_BUNDEM].load("chaos/ucieczka_nastroj.wav");
		g_wBank[SND_HG_LAUGH].load("chaos/hg_laugh.wav");
		g_wBank[SND_SUITCHARGEOK].load("chaos/suitchargeok.wav");
		g_wBank[SND_SMALLMEDKIT].load("chaos/smallmedkit1.wav");
		g_wBank[SND_JETFLY].load("chaos/jetflyby1.wav");
		g_wBank[SND_BEAMSTART5].load("chaos/beamstart5.wav");
		g_wBank[SND_PAIN].load("chaos/pl_pain2.wav");
		g_wBank[SND_XBOW_HIT].load("chaos/xbow_hit.wav");
		g_wBank[SND_GTA_AMMO].load("chaos/gta_ammo.wav");
		g_wBank[SND_BEER1].load("chaos/wrongbeer.wav");
		g_wBank[SND_BEER2].load("chaos/beerresponsible.wav");
		
		g_wBank[SND_MAXWELL].load("chaos/maxwell/maxwell.wav");
		g_wBank[SND_MAXWELL].setLooping(1);
	}

	void EmitSound(int idx)
	{
		if (idx >= SOUNDBANK_SIZE || idx < 0)
			return;

		//g_wBank[idx].setSingleInstance(true);
		gSoloud.play(g_wBank[idx], g_flVolume);
	}

	void StopSound(int idx)
	{
		if (idx >= SOUNDBANK_SIZE || idx < 0)
			return;

		gSoloud.stopAudioSource(g_wBank[idx]);
	}

	void StopAllSounds()
	{
		gSoloud.stopAll();
	}

	void PauseAllSounds()
	{
		gSoloud.setPauseAll(true);
	}

	void UnpauseAllSounds()
	{
		gSoloud.setPauseAll(false);
	}

	void UpdateVolume()
	{
		if (chaos_volume_multiplier)
			chaos_volume_multiplier->value = std::clamp(chaos_volume_multiplier->value, 1.0f, 10.0f);

		if (volume == nullptr)
		{
			volume = pEngfuncs->pfnGetCvarPointer("volume");
		}
		else
		{
			g_flVolume = std::clamp(volume->value, 0.0f, 2.0f) * (chaos_volume_multiplier ? chaos_volume_multiplier->value : 5.0f);
			
			for (int i = 0; i < SOUNDBANK_SIZE; i++)
			{
				g_wBank[i].setVolume(g_flVolume);
			}

			gSoloud.setGlobalVolume(-1.0f);
		}
	}
}