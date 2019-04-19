#include "DXUT.h"
#include "CBullet.h"
#include "CTexture.h"
#include "CEnemy.h"


CBullet::CBullet(Vector3 vStart, Vector3 vDir, float size, float fSpeed, float fDamage)
{
	m_tInfo.vPos = vStart;
	m_vDirection = vDir;
	m_fSpeed = fSpeed;
	m_fDamage = fDamage;
	m_tInfo.iDepth = 1;
	m_tInfo.sTag = "BULLET";

	m_tCollider.SetCollider(size);
	SetTexture("BULLET");
}

CBullet::~CBullet()
{
}

void CBullet::Init()
{
	REGISTERCOLLIDER;
}

void CBullet::Update()
{
	m_tInfo.vPos += m_vDirection * m_fSpeed * DXUTGetElapsedTime();

	m_fRot = D3DXToDegree(atan2f(m_vDirection.y, m_vDirection.x));
}

void CBullet::Render()
{
	IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos, m_fRot);
}

void CBullet::Destroy()
{
	UNREGISTERCOLLIDER;
}

void CBullet::OnCollision(CCollider * _tCol)
{
	if (_tCol->GetOwner()->GetInfo()->sTag == "ENEMY")
	{
		reinterpret_cast<CEnemy*>(_tCol->GetOwner())->TakeDamage(m_fDamage);
		SetDelete(true);
	}
}
