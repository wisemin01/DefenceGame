#include "DXUT.h"
#include "CCoral.h"

#include "CBullet.h"
#include "CTexture.h"

CCoral::CCoral(Vector3 vPos)
	:CTower(vPos, CORAL)
{

}

CCoral::~CCoral()
{
}

void CCoral::Init()
{
	CTower::Init();

	SetTexture("CORAL1");
	SetFrame(0, 10, m_tTowerInfo.AttackSpeed / 11.f);

	vRenderingOffset = Vector3(7, -33, 0);
}

void CCoral::Update()
{
	if (m_pTarget)
	{
		Vector3 dir = m_pTarget->GetInfo()->vPos - m_tInfo.vPos;

		D3DXVec3Normalize(&dir, &dir);

		if (m_fFrameSkip <= GetNowTime() && m_tFrame.CurFrame == 8)
		{
			auto bul = OBJECT.AddObject(OBJKIND::BULLET, new CBullet(m_tInfo.vPos, dir, 20, 800, m_tTowerInfo.AttackDamage));
			m_fFrameSkip = GetNowTime() + m_tTowerInfo.AttackSpeed; bul->GetInfo()->iDepth = 2;
			bul->SetTexture("BLACK_BULLET");
			bul->SetFrame(0, 2, 25);
		}

		Vector3 length = m_pTarget->GetInfo()->vPos - m_tInfo.vPos;

		if (D3DXVec3Length(&length) >= m_tTowerInfo.AttackRange / 2.f)
		{
			m_pTarget = nullptr;
		}
	}

	if (m_pTarget && m_pTarget->GetState() == 4)
	{
		m_pTarget = nullptr;
	}

	m_tFrame.Frame();

}

void CCoral::Render()
{
	IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos + vRenderingOffset);
}

void CCoral::Destroy()
{
	CTower::Destroy();
}

void CCoral::OnCollision(CCollider * _tCol)
{
	CTower::OnCollision(_tCol);
}

void CCoral::Upgrade()
{
	CTower::Upgrade();
	SetTexture("CORAL" + to_string(m_eLevel + 1));

	if (m_eLevel == 1)
		vRenderingOffset = Vector3(-5, -35, 0);
	else if (m_eLevel == 1)
		vRenderingOffset = Vector3(-5, -58, 0);
}
