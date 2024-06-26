#include "includes.h"

float* sys_timescale;

void CFeatureHalfGameSpeed::Init()
{
	CChaosFeature::Init();

	void* Host_InitLocal;
	auto fHost_InitLocal = utils.FindAsync(
		Host_InitLocal,
		patterns::engine::Host_InitLocal,
		[&](auto pattern) {
			switch (pattern - patterns::engine::Host_InitLocal.cbegin())
			{
			default:
			case 0: // HL-9920
				DEBUG_PRINT("Searching sys_timescale in HL-9920 pattern...\n");
				sys_timescale = *reinterpret_cast<float**>(reinterpret_cast<uintptr_t>(Host_InitLocal) + 0x10F);

				if (sys_timescale)
				{
					DEBUG_PRINT("[hw dll] Found sys_timescale at 0x%p.\n", sys_timescale);
					DEBUG_PRINT("[hw dll] sys_timescale == %.01f\n", *sys_timescale);
				}
				break;
			case 1: // HL-8684
				DEBUG_PRINT("Searching sys_timescale in HL-8684 pattern...\n");
				sys_timescale = *reinterpret_cast<float**>(reinterpret_cast<uintptr_t>(Host_InitLocal) + 0x48);

				if (sys_timescale)
				{
					DEBUG_PRINT("[hw dll] Found sys_timescale at 0x%p.\n", sys_timescale);
					DEBUG_PRINT("[hw dll] sys_timescale == %.01f\n", *sys_timescale);
				}
				break;
			}
		});
}

void CFeatureHalfGameSpeed::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
}

void CFeatureHalfGameSpeed::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	*sys_timescale = 1.0f;
}

void CFeatureHalfGameSpeed::OnFrame(double time)
{
	if (!IsActive())
		return;

	*sys_timescale = GetTimescale();
}

const char* CFeatureHalfGameSpeed::GetFeatureName()
{
	return "Half Game Speed";
}

double CFeatureHalfGameSpeed::GetDuration()
{
	return gChaos.GetChaosTime() * 1.15;
}

bool CFeatureHalfGameSpeed::UseCustomDuration()
{
	return true;
}

float CFeatureHalfGameSpeed::GetTimescale()
{
	return 0.5f;
}