#include "DXUT.h"
#include "CSeaAnemone.h"

#include "CBullet.h"
#include "CTexture.h"

CSeaAnemone::CSeaAnemone(Vector3 vPos)
	:CTower(vPos, SEA_ANEMONE)
{

}

CSeaAnemone::~CSeaAnemone()
{
}

void CSeaAnemone::Init()
{
	CTower::Init();

	SetTexture("SEA_ANEMONE1");
	SetFrame(0, 10, m_tTowerInfo.AttackSpeed / 11.f);

	vRenderingOffset = Vector3(0, -30, 0);
}

void CSeaAnemone::Update()
{
	if (m_pTarget)
	{
		Vector3 startVec = (m_tInfo.vPos + Vector3(0, -60, 0));
		Vector3 dir = m_pTarget->GetInfo()->vPos - startVec;

		D3DXVec3Normalize(&dir, &dir);

		if (m_fFrameSkip <= GetNowTime() && m_tFrame.CurFrame == 2)
		{
			auto bul = OBJECT.AddObject(OBJKIND::BULLET, new CBullet(startVec,
				dir, 20, 800, m_tTowerInfo.AttackDamage));
			bul->SetTexture("BLUE_BULLET");
			bul->SetFrame(0, 2, 25);
			m_fFrameSkip = GetNowTime() + m_tTowerInfo.AttackSpeed; bul->GetInfo()->iDepth = 2;
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

void CSeaAnemone::Render()
{
	IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos + vRenderingOffset);
}

void CSeaAnemone::Destroy()
{
	CTower::Destroy();
}

void CSeaAnemone::OnCollision(CCollider * _tCol)
{
	CTower::OnCollision(_tCol);
}

void CSeaAnemone::Upgrade()
{
	CTower::Upgrade();

	SetTexture("SEA_ANEMONE" + to_string(m_eLevel + 1));
}
