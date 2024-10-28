#include "includes.h"

//STB
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GL_CLAMP_TO_EDGE 0x812F

inline int	  ENTINDEX(edict_t* pEdict) { return (*g_engfuncs->pfnIndexOfEdict)(pEdict); }

void _AngleVectors(const Vector angles, Vector forward, Vector right, Vector up)
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;

	angle = angles[0] * (M_PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[1] * (M_PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[2] * (M_PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp * cy;
		forward[1] = cp * sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1 * sr * sp * cy + -1 * cr * -sy);
		right[1] = (-1 * sr * sp * sy + -1 * cr * cy);
		right[2] = -1 * sr * cp;
	}
	if (up)
	{
		up[0] = (cr * sp * cy + -sr * -sy);
		up[1] = (cr * sp * sy + -sr * cy);
		up[2] = cr * cp;
	}
}

float Length(const vec3_t v)
{
	int i;
	float length;

	length = 0;
	for (i = 0; i < 3; i++)
		length += v[i] * v[i];
	length = static_cast<float>(sqrt(length)); // FIXME

	return length;
}

void Draw_FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a)
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_LINES);
	glColor4f(float(r / 255.0f), float(g / 255.0f), float(b / 255.0f), float(a / 255.0f));

	glBegin(GL_QUADS);
	glVertex2f(float(x), float(y));
	glVertex2f(float(w + x), float(y));
	glVertex2f(float(w + x), float(h + y));
	glVertex2f(float(x), float(h + y));
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

char* UTIL_VarArgs(char* format, ...)
{
	va_list		argptr;
	static char		string[1024];

	va_start(argptr, format);
	vsprintf(string, format, argptr);
	va_end(argptr);

	return string;
}

edict_t* UTIL_FindEntityInSphere(edict_t* pStartEntity, const Vector& vecCenter, float flRadius)
{
	edict_t* pentEntity;

	if (pStartEntity)
		pentEntity = pStartEntity;
	else
		pentEntity = NULL;

	pentEntity = FIND_ENTITY_IN_SPHERE(pentEntity, vecCenter, flRadius);

	if (pentEntity)
		return pentEntity;

	return NULL;
}

void UTIL_MakeAimVectors(const Vector& vecAngles)
{
	float rgflVec[3];
	vecAngles.CopyToArray(rgflVec);
	rgflVec[0] = -rgflVec[0];
	MAKE_VECTORS(rgflVec);
}

Vector UTIL_VecToAngles(const Vector& vec)
{
	float rgflVecOut[3];
	VEC_TO_ANGLES(vec, rgflVecOut);
	return Vector(rgflVecOut);
}

void UTIL_MakeVectors(const Vector& vecAngles)
{
	MAKE_VECTORS(vecAngles);
}

// Overloaded to add IGNORE_GLASS
void UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t* pentIgnore, TraceResult* ptr)
{
	TRACE_LINE(vecStart, vecEnd, (igmon == ignore_monsters ? TRUE : FALSE) | (ignoreGlass ? 0x100 : 0), pentIgnore, ptr);
}


void UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, IGNORE_MONSTERS igmon, edict_t* pentIgnore, TraceResult* ptr)
{
	TRACE_LINE(vecStart, vecEnd, (igmon == ignore_monsters ? TRUE : FALSE), pentIgnore, ptr);
}

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

	MESSAGE_BEGIN(MSG_ONE, REG_USER_MSG("ScreenFade", 0), NULL, pEntity);		// use the magic #1 for "one client"

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

// Shake the screen of all clients within radius
// radius == 0, shake all clients
// UNDONE: Allow caller to shake clients not ONGROUND?
// UNDONE: Fix falloff model (disabled)?
// UNDONE: Affect user controls?
void UTIL_ScreenShake(const Vector& center, float amplitude, float frequency, float duration, float radius)
{
	int			i;
	float		localAmplitude;
	ScreenShake	shake;

	shake.duration = FixedUnsigned16(duration, 1 << 12);		// 4.12 fixed
	shake.frequency = FixedUnsigned16(frequency, 1 << 8);	// 8.8 fixed

	if (!(*sv_player) || !((*sv_player)->v.flags & FL_ONGROUND))	// Don't shake if not onground
		return;

	localAmplitude = 0;

	if (radius <= 0)
		localAmplitude = amplitude;
	else
	{
		Vector delta = center - (*sv_player)->v.origin;
		float distance = delta.Length();

		// Had to get rid of this falloff - it didn't work well
		if (distance < radius)
			localAmplitude = amplitude;//radius - distance;
	}
	if (localAmplitude)
	{
		shake.amplitude = FixedUnsigned16(localAmplitude, 1 << 12);		// 4.12 fixed

		MESSAGE_BEGIN(MSG_ONE, REG_USER_MSG("ScreenShake", 0), NULL, (*sv_player));		// use the magic #1 for "one client"

		WRITE_SHORT(shake.amplitude);				// shake amount
		WRITE_SHORT(shake.duration);				// shake lasts this long
		WRITE_SHORT(shake.frequency);				// shake noise frequency

		MESSAGE_END();
	}
}

#define ARMOR_RATIO	 0.2	// Armor Takes 80% of the damage
#define ARMOR_BONUS  0.5	// Each Point of Armor is work 1/x points of health

// I WANNA GET SOME STUFF FROM SERVER DLL BUT DOING THIS SMH - ScriptedSnark
void UTIL_TakeDamage(entvars_t& pevInflictor, float flDamage, int bitsDamageType)
{	
	float flBonus, flRatio;
	float flHealthPrev = pevInflictor.health;

	flBonus = ARMOR_BONUS;
	flRatio = ARMOR_RATIO;

	if (pevInflictor.armorvalue && !(bitsDamageType & (DMG_FALL | DMG_DROWN)))// armor doesn't protect against fall or drown damage!
	{
		float flNew = flDamage * flRatio;

		float flArmor;

		flArmor = (flDamage - flNew) * flBonus;

		// Does this use more armor than we have?
		if (flArmor > pevInflictor.armorvalue)
		{
			flArmor = pevInflictor.armorvalue;
			flArmor *= (1 / flBonus);
			flNew = flDamage - flArmor;
			pevInflictor.armorvalue = 0;
		}
		else
			pevInflictor.armorvalue -= flArmor;

		flDamage = flNew;
	}

	// check for godmode or invincibility
	if (pevInflictor.flags & FL_GODMODE)
		return;

	if (pevInflictor.health <= 0)
		return;

	pevInflictor.dmg_take += flDamage;

	if (pevInflictor.dmg_take)
	{
		MESSAGE_BEGIN(MSG_ONE, REG_USER_MSG("Damage", 0), NULL, pevInflictor.pContainingEntity);
		WRITE_BYTE(0);
		WRITE_BYTE(pevInflictor.dmg_take);
		WRITE_LONG(bitsDamageType);
		WRITE_COORD(0);
		WRITE_COORD(0);
		WRITE_COORD(0);
#ifdef COF_BUILD
		WRITE_BYTE(1);
#endif
		MESSAGE_END();
	}

	if ((int)pevInflictor.health > (int)flDamage)
		pevInflictor.health = int(pevInflictor.health - flDamage);
	else
	{
		pevInflictor.takedamage = DAMAGE_NO;
		pevInflictor.health = -1;
		pevInflictor.deadflag = DEAD_DYING;
		pevInflictor.movetype = MOVETYPE_TOSS;

		if (pevInflictor.pContainingEntity)
		{
			// Tell Ammo Hud that the player is dead
			if (strstr(pEngfuncs->pfnGetGameDirectory(), "czeror")) // HACK FOR COUNTER-STRIKE CONDITION ZERO: DELETED SCENES
				return;

			// TODO: make this thing work for any mod
			MESSAGE_BEGIN(MSG_ONE, REG_USER_MSG("CurWeapon", 0), NULL, pevInflictor.pContainingEntity);
			WRITE_BYTE(0);
			WRITE_BYTE(0XFF);
			WRITE_BYTE(0xFF);
			MESSAGE_END();

			MESSAGE_BEGIN(MSG_ONE, REG_USER_MSG("SetFOV", 0), NULL, pevInflictor.pContainingEntity);
			WRITE_BYTE(0);
			MESSAGE_END();
		}
	}
}

void UTIL_HudMessage(edict_t* pEntity, const hudtextparms_t& textparms, const char* pMessage)
{
	if (!pEntity)
		return;

	MESSAGE_BEGIN(MSG_ONE, SVC_TEMPENTITY, NULL, pEntity);
	WRITE_BYTE(TE_TEXTMESSAGE);
	WRITE_BYTE(textparms.channel & 0xFF);

	WRITE_SHORT(FixedSigned16(textparms.x, 1 << 13));
	WRITE_SHORT(FixedSigned16(textparms.y, 1 << 13));
	WRITE_BYTE(textparms.effect);

	WRITE_BYTE(textparms.r1);
	WRITE_BYTE(textparms.g1);
	WRITE_BYTE(textparms.b1);
	WRITE_BYTE(textparms.a1);

	WRITE_BYTE(textparms.r2);
	WRITE_BYTE(textparms.g2);
	WRITE_BYTE(textparms.b2);
	WRITE_BYTE(textparms.a2);

	WRITE_SHORT(FixedUnsigned16(textparms.fadeinTime, 1 << 8));
	WRITE_SHORT(FixedUnsigned16(textparms.fadeoutTime, 1 << 8));
	WRITE_SHORT(FixedUnsigned16(textparms.holdTime, 1 << 8));

	if (textparms.effect == 2)
		WRITE_SHORT(FixedUnsigned16(textparms.fxTime, 1 << 8));

	if (strlen(pMessage) < 512)
	{
		WRITE_STRING(pMessage);
	}
	else
	{
		char tmp[512];
		strncpy(tmp, pMessage, 511);
		tmp[511] = 0;
		WRITE_STRING(tmp);
	}
	MESSAGE_END();
}


#define TEXTURE_BASEID 12000

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, GLuint* out_texture)
{
	// Load from file
	static int counter;

	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;

	// xWhitey, thank you so much for that idea!
	counter++;
	image_texture = TEXTURE_BASEID + counter;

	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;

	return true;
}

float UTIL_Hue2RGB(float p, float q, float t)
{
	if (t < 0.0f) {
		t = t + 1.0f;
	}

	if (t > 1.0f) {
		t = t - 1.0f;
	}

	if (t < 1.0f / 6.0f) {
		return p + (q - p) * 6.0f * t;
	}

	if (t < 1.0f / 2.0f) {
		return q;
	}

	if (t < 2.0f / 3.0f) {
		return p + (q - p) * ((2.0f / 3.0f) - t) * 6.0f;
	}

	return p;
}

Vector UTIL_HSL2RGB(Vector _HSL)
{
	Vector vecRGB;

	if (_HSL.y == 0.0f) {
		vecRGB.x = _HSL.z;
		vecRGB.y = _HSL.z;
		vecRGB.z = _HSL.z;

		return vecRGB;
	}

	float q = _HSL.z < 0.5f ? _HSL.z * (1.0f + _HSL.y) : _HSL.z + _HSL.y - _HSL.z * _HSL.y;
	float p = 2.0f * _HSL.z - q;

	vecRGB.x = UTIL_Hue2RGB(p, q, _HSL.x + (1.0f / 3.0f));
	vecRGB.y = UTIL_Hue2RGB(p, q, _HSL.x);
	vecRGB.z = UTIL_Hue2RGB(p, q, _HSL.x - (1.0f / 3.0f));

	return vecRGB;
}