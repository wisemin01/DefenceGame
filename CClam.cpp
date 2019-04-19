#include "DXUT.h"
#include "CClam.h"

#include "CCurveBullet.h"
#include "CTexture.h"

CClam::CClam(Vector3 vPos)
	: CTower(vPos, CLAM)
{
}


CClam::~CClam()
{
}

void CClam::Init()
{
	CTower::Init();

	SetTexture("CLAM1");

	vRenderingOffset = Vector3(5, -30, 0);
}

void CClam::Update()
{
	if (m_pTarget)
	{
		Vector3 dir = m_pTarget->GetInfo()->vPos - m_tInfo.vPos;

		D3DXVec3Normalize(&dir, &dir);

		SetFrameAsRotation(dir);

		if (m_fFrameSkip <= GetNowTime())
		{
			OBJECT.AddObject(OBJKIND::BULLET, new CCurveBullet(m_tInfo.vPos,
				&m_pTarget->GetInfo()->vPos, 0.4, 20, m_tTowerInfo.AttackDamage));
			m_fFrameSkip = GetNowTime() + m_tTowerInfo.AttackSpeed;
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

	if (!bPrevInCol)
	{
		SetFrameInIdle();
	}

	bPrevInCol = false;
}

void CClam::Render()
{
	IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos + vRenderingOffset);
}

void CClam::Destroy()
{
	CTower::Destroy();
}

void CClam::OnCollision(CCollider * _tCol)
{
	CObject* other = _tCol->GetOwner();

	if (other->GetInfo()->sTag == "ENEMY")
	{
		bPrevInCol = true;
		if (!m_pTarget)
		{
			if (other->GetState() != 4)
				m_pTarget = other;
		}
	}
}

void CClam::Upgrade()
{
	CTower::Upgrade();

	SetTexture("CLAM" + to_string(m_eLevel + 1));
}

void CClam::SetFrameAsRotation(Vector3 vDir)
{
	Vector2 Direction = vDir;
	D3DXVec2Normalize(&Direction, &Direction);

	float angle = D3DXToDegree(atan2f(Direction.y, Direction.x));

	if (0.f < angle && angle <= 22.5f && !(m_tFrame.CurFrame >= 96 && m_tFrame.CurFrame <= 111))
		SetFrame(96, 111, m_tTowerInfo.AttackSpeed / 16);
	else if (22.5f < angle && angle <= 67.5f && !(m_tFrame.CurFrame >= 112 && m_tFrame.CurFrame <= 127))
		SetFrame(112, 127, m_tTowerInfo.AttackSpeed / 16);
	else if (67.5f < angle && angle <= 112.5f && !(m_tFrame.CurFrame >= 0 && m_tFrame.CurFrame <= 15))
		SetFrame(0, 15, m_tTowerInfo.AttackSpeed / 16);
	else if (112.5f < angle && angle <= 157.5f && !(m_tFrame.CurFrame >= 16 && m_tFrame.CurFrame <= 31))
		SetFrame(16, 31, m_tTowerInfo.AttackSpeed / 16);
	else if (157.5f < angle && angle <= 180.f && !(m_tFrame.CurFrame >= 32 && m_tFrame.CurFrame <= 47))
		SetFrame(32, 47, m_tTowerInfo.AttackSpeed / 16);
	else if (-180 < angle && angle <= -157.5f && !(m_tFrame.CurFrame >= 32 && m_tFrame.CurFrame <= 47))
		SetFrame(32, 47, m_tTowerInfo.AttackSpeed / 16);
	else if (-157.5f < angle && angle <= -112.5f && !(m_tFrame.CurFrame >= 48 && m_tFrame.CurFrame <= 63))
		SetFrame(48, 63, m_tTowerInfo.AttackSpeed / 16);
	else if (-112.5f < angle && angle <= -67.5f && !(m_tFrame.CurFrame >= 64 && m_tFrame.CurFrame <= 79))
		SetFrame(64, 79, m_tTowerInfo.AttackSpeed / 16);
	else if (-67.5f < angle && angle <= -22.5f && !(m_tFrame.CurFrame >= 80 && m_tFrame.CurFrame <= 95))
		SetFrame(80, 95, m_tTowerInfo.AttackSpeed / 16);
	else if (-22.5f < angle && angle <= 0.f && !(m_tFrame.CurFrame >= 96 && m_tFrame.CurFrame <= 111))
		SetFrame(96, 111, m_tTowerInfo.AttackSpeed / 16);
}

void CClam::SetFrameInIdle()
{
	if ((m_tFrame.CurFrame >= 0 && m_tFrame.CurFrame <= 15))
		SetFrame(0, 0, 0);
	else if ((m_tFrame.CurFrame >= 16 && m_tFrame.CurFrame <= 31))
		SetFrame(16, 16, 0);
	else if ((m_tFrame.CurFrame >= 32 && m_tFrame.CurFrame <= 47))
		SetFrame(32, 32, 0);
	else if ((m_tFrame.CurFrame >= 48 && m_tFrame.CurFrame <= 63))
		SetFrame(48, 48, 0);
	else if ((m_tFrame.CurFrame >= 64 && m_tFrame.CurFrame <= 79))
		SetFrame(64, 64, 0);
	else if ((m_tFrame.CurFrame >= 80 && m_tFrame.CurFrame <= 95))
		SetFrame(80, 80, 0);
	else if ((m_tFrame.CurFrame >= 96 && m_tFrame.CurFrame <= 111))
		SetFrame(96, 96, 0);
	else if ((m_tFrame.CurFrame >= 112 && m_tFrame.CurFrame <= 127))
		SetFrame(112, 112, 0);
}
