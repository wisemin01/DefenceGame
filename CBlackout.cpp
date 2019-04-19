#include "DXUT.h"
#include "CBlackout.h"
#include "CTexture.h"

CBlackout::CBlackout(function<void()> pFunc, float fStartAlpha)
	:m_pFunc(pFunc), m_fAlpha(fStartAlpha)
{
}

CBlackout::~CBlackout()
{
}

void CBlackout::Init()
{
	m_tInfo.vPos = V3CENTER;
	if (m_fAlpha == 255)
		m_bType = true;
	else
		m_bType = false;
	SetTexture("BLACK");
}

void CBlackout::Update()
{
	if (m_bType)
		m_fAlpha -= 1;
	else
		m_fAlpha += 1;

	if (m_fAlpha >= 255)
		m_fAlpha = 255;
	if (m_fAlpha <= 0)
		m_fAlpha = 0;

	if (m_fAlpha == 255 || m_fAlpha == 0) {
		m_pFunc();
		SetDelete(true);
	}
}

void CBlackout::Render()
{
	IMAGE.Render(m_pTexture->GetImage(0), m_tInfo.vPos, 0, D3DCOLOR_ARGB((int)m_fAlpha, 255, 255, 255));
}

void CBlackout::Destroy()
{
}
