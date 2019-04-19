#include "DXUT.h"
#include "CObject.h"

#include "CTexture.h"

void CObject::Init()
{
	m_tInfo.vPos = V3ZERO;
	m_tInfo.vScale = Vector3(1, 1, 1);
	m_tInfo.tColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void CObject::Update()
{
	m_tFrame.Frame();
}

void CObject::Render()
{
	IMAGE.ScaleRender(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos,
		Vector3(m_tInfo.vScale.x * m_iFlip, m_tInfo.vScale.y, m_tInfo.vScale.z), 0, m_tInfo.tColor);
}

void CObject::Destroy()
{
}

void CObject::SetFrame(int iStart, int iEnd, DWORD dwDelay)
{
	m_tFrame.SetFrame(iStart, iEnd, dwDelay);
}

void CObject::SetTexture(CTexture * pTexture)
{
	m_pTexture = pTexture;
}

void CObject::SetTexture(const string & key)
{
	m_pTexture = IMAGE.GetImage(key);
}
