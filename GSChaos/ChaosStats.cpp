#include "includes.h"

ChaosStatistics gChaosStats;

namespace ChaosStats
{
	void WriteStats()
	{
		std::ofstream file(CHAOS_STATS_FILE, std::ios::binary | std::ios::trunc);
		if (!file.is_open())
		{
			printf("[CHAOS] Error: Couldn't open chaos_stats.dat.\n");
			return;
		}

		file.write(reinterpret_cast<const char*>(&gChaosStats), sizeof(gChaosStats));
		file.close();
	}

	void ReadStats()
	{
		std::ifstream file(CHAOS_STATS_FILE, std::ios::binary);
		if (!file.is_open())
		{
			printf("[CHAOS] Warning: Stats file not found. Initializing default stats.\n");
			return;
		}

		file.read(reinterpret_cast<char*>(&gChaosStats), sizeof(gChaosStats));
		file.close();

		if (file.gcount() != sizeof(gChaosStats))
		{
			printf("[CHAOS] Warning: Stats file is corrupted. Resetting to default.\n");
			gChaosStats = ChaosStatistics(); // reset all to 0
			WriteStats();
		}

		gChaos.m_iDeaths = gChaosStats.m_iDeaths;
		gChaos.m_iLoads = gChaosStats.m_iLoads;
		gChaos.m_iJumps = gChaosStats.m_iJumps;
		gChaos.m_iCrashes = gChaosStats.m_iCrashes;
	}

	void ResetStats()
	{
		gChaosStats = ChaosStatistics(); // reset all to 0
		WriteStats();
	}

	void SetStatsFromCurrentSession()
	{
		gChaosStats.m_iDeaths = gChaos.m_iDeaths;
		gChaosStats.m_iLoads = gChaos.m_iLoads;
		gChaosStats.m_iJumps = gChaos.m_iJumps;
		gChaosStats.m_iCrashes = gChaos.m_iCrashes;
	}
}