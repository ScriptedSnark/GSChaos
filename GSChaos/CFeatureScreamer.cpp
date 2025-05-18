#include "includes.h"

bool g_bActivatedScreamer = false;
double oldScreamWeapontime;

void CFeatureScreamer::Init()
{
	CChaosFeature::Init();
}

void CFeatureScreamer::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	pEngfuncs->pfnClientCmd(";spk ../../chaos/b_screamclose1;\n");

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY);
	WRITE_BYTE(TE_DLIGHT); // TE index
	WRITE_COORD((*sv_player)->v.origin[0]); // X
	WRITE_COORD((*sv_player)->v.origin[1]); // Y
	WRITE_COORD((*sv_player)->v.origin[2]); // Z
	WRITE_BYTE(25); // Radius 
	WRITE_BYTE(255); // Red
	WRITE_BYTE(0); // Green
	WRITE_BYTE(0); // Blue
	WRITE_BYTE(20); // Life 
	WRITE_BYTE(15); // Decay rate 
	MESSAGE_END();

	g_bActivatedScreamer = true;

	pEngfuncs->pfnWeaponAnim(0, 0);
}

void CFeatureScreamer::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	g_bActivatedScreamer = false;
}

void CFeatureScreamer::OnFrame(double time)
{
	if (!IsActive())
		return;

	int weaponsequence = cl_hl25 ? cl_hl25->weaponsequence : cl->weaponsequence;
	float& weapontime = cl_hl25 ? cl_hl25->weaponstarttime : cl->weaponstarttime;
	if (g_bActivatedScreamer)
	{
		if (weaponsequence != 0)
			weapontime = oldScreamWeapontime;
		else
			oldScreamWeapontime = weapontime;
	}
}

const char* CFeatureScreamer::GetFeatureName()
{
	return "Jumpscare";
}

double CFeatureScreamer::GetDuration()
{
	return 2.0;
}

bool CFeatureScreamer::UseCustomDuration()
{
	return true;
}