#include "includes.h"

//STB
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GL_CLAMP_TO_EDGE 0x812F

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

// Overloaded to add IGNORE_GLASS
void UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t* pentIgnore, TraceResult* ptr)
{
	TRACE_LINE(vecStart, vecEnd, (igmon == ignore_monsters ? TRUE : FALSE) | (ignoreGlass ? 0x100 : 0), pentIgnore, ptr);
}


void UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, IGNORE_MONSTERS igmon, edict_t* pentIgnore, TraceResult* ptr)
{
	TRACE_LINE(vecStart, vecEnd, (igmon == ignore_monsters ? TRUE : FALSE), pentIgnore, ptr);
}

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, GLuint* out_texture)
{
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
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