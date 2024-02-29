#include "includes.h"

#define SLEEPY_TIME			3.0
#define FFADE_IN			0x0000		// Just here so we don't pass 0 into the function
#define FFADE_OUT			0x0001		// Fade out (not in)
#define FFADE_MODULATE		0x0002		// Modulate (don't blend)
#define FFADE_STAYOUT		0x0004		// ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_LONGFADE		0x0008		// used to indicate the fade can be longer than 16 seconds (added for czero)

// This structure is sent over the net to describe a screen fade event
typedef struct
{
	unsigned short 	duration;		// FIXED 4.12 seconds duration
	unsigned short 	holdTime;		// FIXED 4.12 seconds duration until reset (fade & hold)
	short			fadeFlags;		// flags
	byte			r, g, b, a;		// fade to color ( max alpha )
} ScreenFade;

static unsigned short FixedUnsigned16(float value, float scale)
{
	int output;

	output = value * scale;
	if (output < 0)
		output = 0;
	if (output > 0xFFFF)
		output = 0xFFFF;

	return (unsigned short)output;
}

static short FixedSigned16(float value, float scale)
{
	int output;

	output = value * scale;

	if (output > 32767)
		output = 32767;

	if (output < -32768)
		output = -32768;

	return (short)output;
}

void UTIL_ScreenFadeBuild(ScreenFade& fade, const Vector& color, float fadeTime, float fadeHold, int alpha, int flags)
{
	fade.duration = FixedUnsigned16(fadeTime, 1 << 12);		// 4.12 fixed
	fade.holdTime = FixedUnsigned16(fadeHold, 1 << 12);		// 4.12 fixed
	fade.r = (int)color.x;
	fade.g = (int)color.y;
	fade.b = (int)color.z;
	fade.a = alpha;
	fade.fadeFlags = flags;
}


void UTIL_ScreenFadeWrite(const ScreenFade& fade, edict_t* pEntity)
{
	if (!pEntity)
		return;

	MESSAGE_BEGIN(MSG_ONE, REG_USER_MSG("ScreenFade", sizeof(ScreenFade)), NULL, pEntity);		// use the magic #1 for "one client"

	WRITE_SHORT(fade.duration);		// fade lasts this long
	WRITE_SHORT(fade.holdTime);		// fade lasts this long
	WRITE_SHORT(fade.fadeFlags);		// fade type (in / out)
	WRITE_BYTE(fade.r);				// fade red
	WRITE_BYTE(fade.g);				// fade green
	WRITE_BYTE(fade.b);				// fade blue
	WRITE_BYTE(fade.a);				// fade blue

	MESSAGE_END();
}

void UTIL_ScreenFade(edict_t* pEntity, const Vector& color, float fadeTime, float fadeHold, int alpha, int flags)
{
	ScreenFade	fade;

	UTIL_ScreenFadeBuild(fade, color, fadeTime, fadeHold, alpha, flags);
	UTIL_ScreenFadeWrite(fade, pEntity);
}

void CFeatureSleepy::Init()
{
	CChaosFeature::Init();
}

void CFeatureSleepy::ActivateFeature()
{
	CChaosFeature::ActivateFeature();
	m_bActivated = true;

	m_flSleepyTime = gChaos.GetGlobalTime() + SLEEPY_TIME;
}

void CFeatureSleepy::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();
	m_bActivated = false;

	UTIL_ScreenFade((*sv_player), Vector(0, 0, 0), 0.0f, 0.0f, 0, 0);
}

void CFeatureSleepy::OnFrame(double time)
{
	if (!m_bActivated)
		return;

	if (gChaos.GetGlobalTime() >= m_flSleepyTime)
	{
		UTIL_ScreenFade((*sv_player), Vector(0, 0, 0), 1.75f, 0.1f, 255, FFADE_IN);
		m_flSleepyTime = gChaos.GetGlobalTime() + SLEEPY_TIME;
	}
}

const char* CFeatureSleepy::GetFeatureName()
{
	return "Sleepy";
}