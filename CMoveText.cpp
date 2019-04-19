#include "DXUT.h"
#include "CMoveText.h"


CMoveText::CMoveText(const string & sText, Vector3 vPos, D3DCOLORVALUE colorValue, Vector3 vVel, float fEnd, bool IsDownAlpha, float fFontSize)
	: sText(sText), vVelocity(vVel), bIsDownAlpha(IsDownAlpha),colorValue (colorValue), fSize(fFontSize)
{
	m_tInfo.vPos = vPos;
	fEndTime = fEnd;
	m_tInfo.tColor = (D3DCOLOR)D3DCOLOR_ARGB((int)colorValue.a,
		(int)colorValue.r, (int)colorValue.g, (int)colorValue.b);

	m_tInfo.iDepth = 11;
}

CMoveText::~CMoveText()
{
}

void CMoveText::Init()
{
	if (fEndTime != 0)
		fEndTime += GetNowTime();
}

void CMoveText::Update()
{
	m_tInfo.vPos += vVelocity * DXUTGetElapsedTime();

	if (bIsDownAlpha)
	{
		colorValue.a -= fAlphaDown;
		m_tInfo.tColor = (D3DCOLOR)D3DCOLOR_ARGB((int)colorValue.a,
			(int)colorValue.r, (int)colorValue.g, (int)colorValue.b);
	}

	if (fEndTime != 0 && fEndTime <= GetNowTime())
	{
		SetDelete(true);
	}

	if (colorValue.a <= 0)
		SetDelete(true);
}

void CMoveText::Render()
{
	IMAGE.PrintCenterText(sText, m_tInfo.vPos.x, m_tInfo.vPos.y, fSize, m_tInfo.tColor);
}

void CMoveText::Destroy()
{
}
