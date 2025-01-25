/**
 * Copyright - ScriptedSnark, 2024-2025.
 * ChaosStats.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef CHAOSSTATS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in ChaosStats.h
#else //CHAOSSTATS_H_RECURSE_GUARD

#define CHAOSSTATS_H_RECURSE_GUARD

#ifndef CHAOSSTATS_H_GUARD
#define CHAOSSTATS_H_GUARD
#pragma once

#ifdef __cplusplus

#define CHAOS_STATS_FILE "chaos/chaos_stats.dat"

struct ChaosStatistics
{
	int m_iDeaths = 0;
	int m_iLoads = 0;
	int m_iJumps = 0;
	int m_iCrashes = 0;
};

namespace ChaosStats
{
	void WriteStats();
	void ReadStats();
	void SetStatsFromCurrentSession();
}

#else //!__cplusplus
#error C++ compiler required to compile ChaosStats.h
#endif //__cplusplus

#endif //CHAOSSTATS_H_GUARD

#undef CHAOSSTATS_H_RECURSE_GUARD
#endif //CHAOSSTATS_H_RECURSE_GUARD