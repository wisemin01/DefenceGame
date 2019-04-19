#include "DXUT.h"
#include "CExplode.h"
#include "CTexture.h"
#include "CEnemy.h"

CExplode::CExplode(Vector3 vPos, float Damage)
	:fDamage(Damage)
{
	m_tInfo.vPos = vPos;
}

CExplode::~CExplode()
{
}

void CExplode::Init()
{
	SetTexture("EXPLODE");
	SetFrame(0, m_pTexture->Length() - 1, 100);
	endAttack = false;
	m_tInfo.iDepth = 1;

	m_tCollider.SetCollider(200);
	REGISTERCOLLIDER;
}

void CExplode::Update()
{
	if (endAttack)
	{
		UNREGISTERCOLLIDER;
	}
	if (m_tFrame.CurFrame == m_tFrame.EndFrame)
	{
		SetDelete(true);
	}

	m_tFrame.Frame();
}

void CExplode::Render()
{
	IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos);
}

void CExplode::Destroy()
{
	UNREGISTERCOLLIDER;
}

void CExplode::OnCollision(CCollider * _tCol)
{
	if (_tCol->GetOwner()->GetInfo()->sTag == "ENEMY")
	{
		reinterpret_cast<CEnemy*>(_tCol->GetOwner())->TakeDamage(fDamage);
		endAttack = true;
	}
}
