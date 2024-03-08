#include "includes.h"

edict_t** sv_player;

void CFeatureSet1HP::Init()
{
	CChaosFeature::Init();

	void* SV_ExecuteClientMessage;
	auto fSV_ExecuteClientMessage = utils.FindAsync(
		SV_ExecuteClientMessage,
		patterns::engine::SV_ExecuteClientMessage,
		[&](auto pattern) {
			switch (pattern - patterns::engine::SV_ExecuteClientMessage.cbegin())
			{
			default:
			case 0: // HL25
			{
				DEBUG_PRINT("Searching sv_player in HL25 pattern...\n");
				sv_player = *reinterpret_cast<edict_t***>(reinterpret_cast<uintptr_t>(SV_ExecuteClientMessage) + 0x1B9);

				if (sv_player)
				{
					DEBUG_PRINT("[hw dll] Found sv_player at 0x%p.\n", sv_player);
				}

				break;
			}
			case 1: // HL-Steampipe
			{
				DEBUG_PRINT("Searching sv_player in HL-Steampipe pattern...\n");
				sv_player = *reinterpret_cast<edict_t***>(reinterpret_cast<uintptr_t>(SV_ExecuteClientMessage) + 0x9B);

				if (sv_player)
				{
					DEBUG_PRINT("[hw dll] Found sv_player at 0x%p.\n", sv_player);
				}

				break;
			}
			case 2: // HL-4554
			{
				DEBUG_PRINT("Searching sv_player in HL-4554 pattern...\n");
				sv_player = *reinterpret_cast<edict_t***>(reinterpret_cast<uintptr_t>(SV_ExecuteClientMessage) + 22);

				if (sv_player)
				{
					DEBUG_PRINT("[hw dll] Found sv_player at 0x%p.\n", sv_player);
				}

				break;
			}
			}
		});
}

void CFeatureSet1HP::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	(*sv_player)->v.health = 1;
}

void CFeatureSet1HP::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
}

const char* CFeatureSet1HP::GetFeatureName()
{
	return "Set 1 HP";
}