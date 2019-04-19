#include "DXUT.h"
#include "CTower.h"
#include "CTexture.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CMoveText.h"

CTowerInfo CTower::g_tTowerInfo[TOWERKIND_END][LEVEL_END];

CTower::CTower(Vector3 vPos, int iKind)
{
	m_tInfo.vPos = vPos;
	m_tTowerInfo = GetStaticInfo(iKind, LEVEL1);

	m_eKind = iKind;
	m_eLevel = LEVEL1;

	m_tInfo.iDepth = 1;
	m_fFrameSkip = 0;
	m_pTarget = nullptr;

	vRenderingOffset = V3ZERO;
}

CTower::~CTower()
{
}

void CTower::Init()
{
	m_tCollider.SetCollider(m_tTowerInfo.AttackRange);
	REGISTERCOLLIDER;

	DATA.AddGold(-m_tTowerInfo.Cost);
	auto mt = OBJECT.AddUI(UIOBJKIND::SCROLL, new CMoveText("-" +
		to_string((int)m_tTowerInfo.Cost) + " GOLD", m_tInfo.vPos, { 255,140,50,255 }, Vector3(0, -20, 0), 2000, true));
	mt->GetInfo()->iDepth = 6;
}

void CTower::Update()
{
	if (m_pTarget)
	{
		Vector3 dir = m_pTarget->GetInfo()->vPos - m_tInfo.vPos;

		D3DXVec3Normalize(&dir, &dir);

		if (m_fFrameSkip <= GetNowTime())
		{
			OBJECT.AddObject(OBJKIND::BULLET, new CBullet(m_tInfo.vPos, dir, 20, 1000, m_tTowerInfo.AttackDamage));
			m_fFrameSkip = GetNowTime() + m_tTowerInfo.AttackSpeed;
		}

		Vector3 length = m_pTarget->GetInfo()->vPos - m_tInfo.vPos;

		if (D3DXVec3Length(&length) >= m_tTowerInfo.AttackRange / 2.f)
		{
			m_pTarget = nullptr;
		}
	}

	if (m_pTarget && m_pTarget->GetState() == 3)
	{
		m_pTarget = nullptr;
	}

	m_tFrame.Frame();
}

void CTower::Render()
{
	IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos);
}

void CTower::Destroy()
{
	UNREGISTERCOLLIDER;
}

void CTower::OnCollision(CCollider * _tCol)
{
	CObject* other = _tCol->GetOwner();

	if (other->GetInfo()->sTag == "ENEMY")
	{
		if (!m_pTarget)
		{
			if (other->GetState() != 4)
				m_pTarget = other;
		}
	}
}

bool CTower::IsCanUpgrade()
{
	if (g_tTowerInfo[m_eKind][m_eLevel + 1].Cost >= DATA.GetGold())
	{
		auto mt = new CMoveText("Upgrade requires "
			+ to_string((int)g_tTowerInfo[m_eKind][m_eLevel + 1].Cost) + " Gold.",
			Vector3(WINSIZEX / 2, 200, 0), { 255,50,50,255 }, Vector3(0, -10, 0), 4000, true, 45);
		mt->SetAlphaDownSpeed(1);
		OBJECT.AddUI(UIOBJKIND::SCREEN, mt);
		return false;
	}
	if (m_eLevel >= LEVEL3)
	{
		OBJECT.AddUI(UIOBJKIND::SCROLL, new CMoveText("Tower is max level.", m_tInfo.vPos, { 255,255,255,255 }, Vector3(0, -20, 0), 2000, true, 30));
		return false;
	}
	return true;
}

void CTower::Upgrade()
{
	m_eLevel++;

	m_tTowerInfo = g_tTowerInfo[m_eKind][m_eLevel];

	m_tCollider.SetCollider(m_tTowerInfo.AttackRange);

	DATA.AddGold(-m_tTowerInfo.Cost);
}

void CTower::Sell()
{
	float returnGold = 0;

	for (int i = 0; i <= m_eLevel; i++)
		returnGold += g_tTowerInfo[m_eKind][i].Cost;

	returnGold *= 0.5f;

	DATA.AddGold(returnGold);
	OBJECT.AddUI(UIOBJKIND::SCROLL, new CMoveText("+" + to_string((int)returnGold) +
		" GOLD", m_tInfo.vPos, { 50,255,140,255 }, Vector3(0, -20, 0), 2000, true));
	SetDelete(true);
}

bool CTower::IsCanDrop(float fNowGold, int iKind)
{
	if (g_tTowerInfo[iKind][0].Cost <= fNowGold)
		return true;
	else
	{
		auto mt = new CMoveText("Drop requires "
			+ to_string((int)g_tTowerInfo[iKind][0].Cost) + " Gold.",
			Vector3(WINSIZEX / 2, 200, 0), { 255,50,50,255 }, Vector3(0, -10, 0), 4000, true, 45);
		mt->SetAlphaDownSpeed(1);
		OBJECT.AddUI(UIOBJKIND::SCREEN, mt);
		return false;
	}
}
