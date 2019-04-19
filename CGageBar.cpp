#include "DXUT.h"
#include "CGageBar.h"

#include "CTexture.h"

CGageBar::CGageBar(float * Max, float * Cur,
	Vector3 * TargetPos, Vector3 Offset, CTexture * Texture)
	:m_fMax(Max),m_fCur(Cur),m_vTargetPos(TargetPos),m_vOffset(Offset)
{
	m_pTexture = Texture;
	m_tInfo.iDepth = 10;
}

CGageBar::~CGageBar()
{
}

void CGageBar::Init()
{
	auto info = m_pTexture->GetImage(1)->info;

	m_tInfo.vScale = Vector3(info.Width, info.Height, 0);

}

void CGageBar::Update()
{
	float percent = *m_fCur / *m_fMax;

	m_fWidth = m_tInfo.vScale.x * percent;
}

void CGageBar::Render()
{
	Vector3 renderPos = *m_vTargetPos + m_vOffset;

	IMAGE.Render(m_pTexture->GetImage(0), renderPos);
	RECT rc = { 0, 0, m_fWidth, m_tInfo.vScale.y };
	IMAGE.CropRender(m_pTexture->GetImage(1), renderPos, rc);
}

void CGageBar::Destroy()
{
}
