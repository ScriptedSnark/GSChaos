/**
 * Copyright - ScriptedSnark, 2024-2025.
 * CFeatureGalangaAmbush.h
 *
 * Project (GSChaos) header file
 * Authors: StereoBucket.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CFEATUREGALANGAAMBUSH_H_RECURSE_GUARD
#error Recursive header files inclusion detected in CFeatureGalangaAmbush.h
#else //CFEATUREGALANGAAMBUSH_H_RECURSE_GUARD

#define CFEATUREGALANGAAMBUSH_H_RECURSE_GUARD

#ifndef CFEATUREGALANGAAMBUSH_H_GUARD
#define CFEATUREGALANGAAMBUSH_H_GUARD
#pragma once

#ifdef __cplusplus

class CFeatureGalangaAmbush : public CChaosFeature
{
	void Init() override;
	void ActivateFeature() override;
	void DeactivateFeature() override;
	void OnFrame(double time) override;
	const char* GetFeatureName() override;
	void Restore() override;
private:
	static void Precache();
	double m_flSpawnTime;
	bool m_bSpawned;
	struct galangese {
		char *soundpath;
		double duration;
	};
	double m_lastplayed;
	double m_curduration;
	std::vector<edict_t*> m_vGalangas;
	static const galangese galangaSounds[9];
};

#else //!__cplusplus
#error C++ compiler required to compile CFeatureGalangaAmbush.h
#endif //__cplusplus

#endif //CFEATUREGALANGAAMBUSH_H_GUARD

#undef CFEATUREGALANGAAMBUSH_H_RECURSE_GUARD
#endif //CFEATUREGALANGAAMBUSH_H_RECURSE_GUARD