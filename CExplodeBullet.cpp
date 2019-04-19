#include "DXUT.h"
#include "CExplodeBullet.h"

#include "CExplode.h"

CExplodeBullet::CExplodeBullet(Vector3 vStart, Vector3 vDir, float size, float fSpeed, float fDamage, float fLifeTime)
	:CBullet(vStart, vDir, size, fSpeed, fDamage), m_fLifeTime(fLifeTime)
{
}

CExplodeBullet::~CExplodeBullet()
{
}

void CExplodeBullet::Init()
{
	m_fLifeTime += GetNowTime();
}

void CExplodeBullet::Update()
{
	if (m_fLifeTime <= GetNowTime())
	{
		OBJECT.AddObject(OBJKIND::EFFECT, new CExplode(m_tInfo.vPos, m_fDamage));
		SetDelete(true);
	}
	CBullet::Update();
}

void CExplodeBullet::Render()
{
	CBullet::Render();
}

void CExplodeBullet::Destroy()
{
}

void CExplodeBullet::OnCollision(CCollider * col)
{
	if (col->GetOwner()->GetInfo()->sTag == "ENEMY")
	{
		OBJECT.AddObject(OBJKIND::EFFECT, new CExplode(m_tInfo.vPos, m_fDamage));
		SetDelete(true);
	}
}
