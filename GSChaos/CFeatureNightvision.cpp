#include "includes.h"

// TODO: move it to utils
#define SetBits(flBitVector, bits) ((flBitVector) = (int)(flBitVector) | (bits))
#define ClearBits(flBitVector, bits) ((flBitVector) = (int)(flBitVector) & ~(bits))
#define FBitSet(flBitVector, bit) (((int)(flBitVector) & (bit)) != 0)

int LoadSprite(const char* pszName)
{
	int i;
	char sz[256];

	if (ScreenWidth < 640)
		i = 320;
	else
		i = 640;

	sprintf(sz, pszName, i);

	return pEngfuncs->pfnSPR_Load(sz);
}

void CFeatureNightvision::Init()
{
	CChaosFeature::Init();
}

void CFeatureNightvision::ActivateFeature()
{
	CChaosFeature::ActivateFeature();

	m_nvSprite = LoadSprite("../chaos/of_nv_b.spr");

	// Get the number of frames available in this sprite.
	m_nFrameCount = pEngfuncs->pfnSPR_Frames(m_nvSprite);

	// current frame.
	m_iFrame = 0;

	SetBits((*sv_player)->v.effects, EF_BRIGHTLIGHT);
}

void CFeatureNightvision::DeactivateFeature()
{
	CChaosFeature::DeactivateFeature();

	ClearBits((*sv_player)->v.effects, EF_BRIGHTLIGHT);
}

void CFeatureNightvision::Draw()
{
	if (!IsActive())
		return;

	// Top left of the screen.
	int x, y;
	x = y = 0;

	// Reset the number of frame if we are at last frame.
	if (m_iFrame >= m_nFrameCount)
		m_iFrame = 0;

	const int nvgSpriteWidth = pEngfuncs->pfnSPR_Width(m_nvSprite, 0);
	const int nvgSpriteHeight = pEngfuncs->pfnSPR_Height(m_nvSprite, 0);

	const int colCount = (int)ceil(ScreenWidth / (float)nvgSpriteWidth);
	const int rowCount = (int)ceil(ScreenHeight / (float)nvgSpriteHeight);

	//
	// draw nightvision scanlines sprite.
	//
	pEngfuncs->pfnSPR_Set(m_nvSprite, 0, 170, 0);

	int i, j;
	for (i = 0; i < rowCount; ++i) // height
	{
		for (j = 0; j < colCount; ++j) // width
		{
			pEngfuncs->pfnSPR_DrawAdditive(m_iFrame, x + (j * nvgSpriteWidth), y + (i * nvgSpriteHeight), NULL);
		}
	}

	// Increase sprite frame.
	m_iFrame++;
}

const char* CFeatureNightvision::GetFeatureName()
{
	return "Nightvision";
}

double CFeatureNightvision::GetDuration()
{
	return gChaos.GetChaosTime() * 1.6;
}

bool CFeatureNightvision::UseCustomDuration()
{
	return true;
}

bool CFeatureNightvision::CanBeInfinite()
{
	return true;
}