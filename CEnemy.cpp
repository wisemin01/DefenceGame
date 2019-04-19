#include "DXUT.h"
#include "CEnemy.h"

#include "CTexture.h"
#include "CMoveText.h"
#include "CCore.h"
#include "CGageBar.h"

std::vector<Vector3> CEnemy::g_vEnemyLoad[3][2];

CEnemy::CEnemy(int stageType, float enemyHp, float enemySpeed,
	float deathCost, float attackDamage, CObject* pSpawn)
	: m_fSpeed(enemySpeed), m_fCurHp(enemyHp), m_fMaxHp(enemyHp), m_fDeathCost(deathCost), m_pSpawnObj(pSpawn)
	, m_fAttackDamage(attackDamage)
{
	m_vMyLoad = g_vEnemyLoad[stageType][stageType == 1 ? rand() % 2 : 0];
	m_tInfo.sTag = "ENEMY";
	m_iFrameInterval = 9;
	SetTexture(nullptr);
}

CEnemy::CEnemy(int stageType, float enemyHp, float enemySpeed,
	float deathCost, float attackDamage, CTexture * pTexture, int FrameInterval)
	: m_fSpeed(enemySpeed), m_fCurHp(enemyHp), m_fMaxHp(enemyHp), m_fDeathCost(deathCost)
	, m_fAttackDamage(attackDamage),m_iFrameInterval(FrameInterval)
{
	m_vMyLoad = g_vEnemyLoad[stageType][stageType == 1 ? rand() % 2 : 0];
	m_tInfo.sTag = "ENEMY";
	SetTexture(pTexture);
}


CEnemy::~CEnemy()
{
}

void CEnemy::Init()
{
	m_tInfo.vPos = *m_vMyLoad.begin();

	m_iLastLoadNum = m_vMyLoad.size();
	m_iCurLoadNum = 0;

	m_iState = MOVE_SIDE;
	SetFrameAsState();

	if (!m_pTexture)
		SetTexture("SLIME");

	m_tCollider.SetCollider(75);
	REGISTERCOLLIDER;

	if (m_pSpawnObj) {
		OBJECT.AddUI(UIOBJKIND::SCREEN, m_pSpawnObj);
		m_pSpawnObj = nullptr;
	}

	SettingOffset(m_pTexture);

	m_myHpBar = new CGageBar(&m_fMaxHp, &m_fCurHp, &m_tInfo.vPos,
		Vector3(0,-30,0), IMAGE.GetImage("SMALL_BAR"));
	OBJECT.AddUI(UIOBJKIND::SCROLL, m_myHpBar);
}

void CEnemy::Update()
{
	switch (m_iState)
	{
	case MOVE_SIDE:
	case MOVE_FRONT:
	case MOVE_BACK: MoveUpdate();	break;
	case ATTACK:	AttackUpdate();	break;
	case DEATH:		DeathUpdate();	break;
	}

	m_tFrame.Frame();

	if (m_fSlowTime <= GetNowTime())
	{
		m_bIsSlowMode = false;
		m_fSlowOffset = 1.0f;
		m_fSlowTime   = 0.0f;
	}
}

void CEnemy::Render()
{
	IMAGE.ScaleRender(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos + m_vOffset, Vector3(m_iFlip, 1, 1));
}

void CEnemy::Destroy()
{
	UNREGISTERCOLLIDER;

	if (m_pSpawnObj)
	{
		SAFE_DELETE(m_pSpawnObj);
	}
}

void CEnemy::OnCollision(CCollider * col)
{
	if (m_iState != ATTACK && m_iState != DEATH &&
		col->GetOwner()->GetInfo()->sTag == "CORE")
	{
		m_iState = ATTACK;
		SetFrameAsState();
		reinterpret_cast<CCore*>(col->GetOwner())->TakeDamage(m_fAttackDamage);
	}
}

void CEnemy::SetSlow(float fSlowTime, float vSlowOffset)
{
	float compareSlow = fSlowTime + GetNowTime();
	
	if (compareSlow > m_fSlowTime)
		m_fSlowTime = compareSlow;

	if (vSlowOffset < m_fSlowOffset)
		m_fSlowOffset = vSlowOffset;
	
	m_bIsSlowMode = true;
}

void CEnemy::TakeDamage(float damage)
{
	m_fCurHp -= damage;

	D3DCOLORVALUE value = { 255,140,50,255 }; // 주황색
	int size = 35;
	int lifeTime = 1000;

	if (damage < 0)
		value = { 50,255,140, 255 }; // 회복 ( 초록 )
	else if (damage >= 100)
	{
		value = { 255,50,50,255 }; // 강한 데미지 ( 빨강 )
		size *= 1.3; // 폰트 크기 1.3배
		lifeTime = 1800;
	}
	auto hpUI = OBJECT.AddUI(UIOBJKIND::SCROLL,
		new CMoveText((damage > 0 ? "-" : "+") + to_string((int)abs(damage)),
			m_tInfo.vPos + Vector3(GetRand(-10, 10), GetRand(-5, 5), 0), value, Vector3(0, -80, 0), lifeTime, true, size));
	hpUI->GetInfo()->iDepth = 11;

	if (m_fCurHp < 0)
		m_fCurHp = 0;
}

void CEnemy::MoveUpdate()
{
	int prev = m_iState;

	Vector3 m_vDir = m_vMyLoad[m_iCurLoadNum + 1] - m_tInfo.vPos;

	if (D3DXVec3Length(&m_vDir) <= m_fSpeed * DXUTGetElapsedTime())
	{
		m_iCurLoadNum++;

		if (m_iCurLoadNum + 1 == m_iLastLoadNum)
		{
			m_iState = ATTACK;

			if (m_vDir.x > 0) // 오른쪽
				m_iFlip = 1;
			else //왼쪽
				m_iFlip = -1;
		}
	}
	else
	{
		Vector3 vVel;
		D3DXVec3Normalize(&vVel, &m_vDir);

		m_tInfo.vPos += vVel * m_fSpeed * DXUTGetElapsedTime()
			* (m_bIsSlowMode ? m_fSlowOffset : 1.0f);
	}

	if (m_iState != ATTACK && m_iState != DEATH)
	{
		if (abs(m_vDir.x) > abs(m_vDir.y))
		{
			// 옆쪽으로 움직인다
			m_iState = MOVE_SIDE;
			if (m_vDir.x > 0) // 오른쪽
				m_iFlip = -1;
			else //왼쪽
				m_iFlip = 1;
		}
		else
		{
			// 위, 아래로 움직인다.
			if (m_vDir.y > 0) // 아래
			{
				m_iState = MOVE_FRONT;
			}
			else // 위
			{
				m_iState = MOVE_BACK;
			}
		}
	}

	if (m_fCurHp == 0)
	{
		m_iState = DEATH;
		DATA.AddGold(m_fDeathCost);
		OBJECT.AddUI(UIOBJKIND::SCROLL, new CMoveText("+" + to_string((int)m_fDeathCost) +
			"G", m_tInfo.vPos, { 50,255,140,255 }, Vector3(0, -20, 0), 2000, true));
	}

	if (prev != m_iState)
		SetFrameAsState();
}

void CEnemy::AttackUpdate()
{
	if (m_vDir.x > 0) // 오른쪽
		m_iFlip = -1;
	else //왼쪽
		m_iFlip = 1;

	if (m_tFrame.CurFrame == m_iFrameInterval * 4 - 1)
	{
		m_iState = DEATH;
		SetFrameAsState();
	}
}

void CEnemy::DeathUpdate()
{
	if (m_vDir.x > 0) // 오른쪽
		m_iFlip = -1;
	else //왼쪽
		m_iFlip = 1;

	if (m_myHpBar) {
		UNREGISTERCOLLIDER;
		m_myHpBar->SetDelete(true);
		m_myHpBar = nullptr;
	}

	if (m_tFrame.CurFrame == m_iFrameInterval * 5 - 1)
	{
		SetDelete(true);
	}
}

void CEnemy::SettingOffset(CTexture * pTexture)
{
	if (pTexture == IMAGE.GetImage("SLIME"))
		m_vOffset = Vector3(0, -20, 0);
	else if (pTexture == IMAGE.GetImage("SLIME2"))
		m_vOffset = Vector3(0, -10, 0);
	else if (pTexture == IMAGE.GetImage("SOLDIER"))
		m_vOffset = Vector3(0, -40, 0);

}

void CEnemy::SetEnemyLoad(const std::vector<Vector3>& vecLoad, int stageType, int loadType)
{
	g_vEnemyLoad[stageType][loadType] = vecLoad;
}

void CEnemy::SetFrameAsState()
{
	switch (m_iState)
	{
	case MOVE_SIDE: SetFrame(m_iFrameInterval, m_iFrameInterval * 2 - 1, 120);
		break;
	case MOVE_FRONT: SetFrame(0, m_iFrameInterval - 1, 120);
		break;
	case MOVE_BACK: SetFrame(m_iFrameInterval * 2, m_iFrameInterval * 3 - 1, 120);
		break;
	case ATTACK: SetFrame(m_iFrameInterval * 3, m_iFrameInterval * 4 - 1, 120);
		break;
	case DEATH: SetFrame(m_iFrameInterval * 4, m_iFrameInterval * 5 - 1, 120);
		break;
	}
}
