#ifdef CHAOSLOUDMANAGER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in ChaosLoudManager.h
#else //CHAOSLOUDMANAGER_H_RECURSE_GUARD

#define CHAOSLOUDMANAGER_H_RECURSE_GUARD

#ifndef CHAOSLOUDMANAGER_H_GUARD
#define CHAOSLOUDMANAGER_H_GUARD
#pragma once

#ifdef __cplusplus

enum
{
	MUSIC_JESUS = 0,
	MUSIC_OPFOR01,
	SND_SLAP,
	SND_GTA3_WPN_PICKUP,
	SND_GTA3_ITEM_PICKUP,
	SND_GTA3_NOTIFY,
	SND_GTAVC_WPN_PICKUP,
	SND_GTAVC_ITEM_PICKUP,
	SND_GTAVC_NOTIFY,
	SND_LASAGNA,
	SND_LOBOTOMY,
	SND_TOTEM,
	SND_RESPECT,
	SND_BUNDEM,
	SND_HG_LAUGH,
	SND_SUITCHARGEOK,
	SND_SMALLMEDKIT,
	SND_JETFLY,
	SND_BEAMSTART5,
	SND_PAIN,
	SND_XBOW_HIT,
	SOUNDBANK_SIZE
};

namespace ChaosLoud
{
	void LoadSounds();
	void EmitSound(int idx);
	void StopSound(int idx);
	void StopAllSounds();
	void PauseAllSounds();
	void UnpauseAllSounds();
	void UpdateVolume();

	extern SoLoud::Wav g_wBank[SOUNDBANK_SIZE];
}

#else //!__cplusplus
#error C++ compiler required to compile ChaosLoudManager.h
#endif //__cplusplus

#endif //CHAOSLOUDMANAGER_H_GUARD

#undef CHAOSLOUDMANAGER_H_RECURSE_GUARD
#endif //CHAOSLOUDMANAGER_H_RECURSE_GUARD