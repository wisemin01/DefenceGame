#include "DXUT.h"
#include "CMoveObject.h"
#include "CTexture.h"

CMoveObject::CMoveObject(Vector3 vStart, Vector3 vVel, float fEndTime)
	:m_vVel(vVel), m_fEndTime(fEndTime)
{
	m_tInfo.vPos = vStart;
	m_tInfo.vScale = Vector3(1, 1, 1);
	m_tInfo.tColor = 0xffffffff;
}

CMoveObject::~CMoveObject()
{
}

void CMoveObject::Init()
{
	m_fEndTime += GetNowTime();
}

void CMoveObject::Update()
{
	if (m_fEndTime <= GetNowTime())
		SetDelete(true);

	m_tInfo.vPos += m_vVel * DXUTGetElapsedTime();
}

void CMoveObject::Render()
{
	IMAGE.ScaleRender(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos,
		Vector3(m_tInfo.vScale.x * m_iFlip, m_tInfo.vScale.y, 1), 0, m_tInfo.tColor);
}

void CMoveObject::Destroy()
{

}
