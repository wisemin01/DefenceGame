#include "DXUT.h"
#include "CCore.h"
#include "CMoveText.h"
#include "CTexture.h"
#include "CGageBar.h"
#include "CExplode.h"
#include "CBlackout.h"

CCore::CCore(Vector3 vPos, float fHp, CTexture * pTex)
	: m_fMaxHp(fHp),m_fCurHp(fHp)
{
	m_tInfo.vPos = vPos;
	m_pTexture = pTex;
	m_tInfo.sTag = "CORE";
	m_tInfo.iDepth = 6;

	m_vOffset = Vector3(0, -75, 20);
	m_vHpBar = Vector3(500, 30, 0);
}

CCore::~CCore()
{
}

void CCore::Init()
{
	m_tFrame.SetFrame(0, m_pTexture->Length() - 1, 200);
	m_tCollider.SetCollider(350);
	REGISTERCOLLIDER;

	m_pMyHpBar = new CGageBar(&m_fMaxHp, &m_fCurHp, &m_tInfo.vPos,
		Vector3(0, -180, 20), IMAGE.GetImage("BIG_BAR"));
	OBJECT.AddUI(UIOBJKIND::SCROLL, m_pMyHpBar);
}

void CCore::Update()
{
	switch (m_iState)
	{
	case CORE_STATE::IDLE:

		if (m_fCurHp == 0) {
			m_iState = DEATH;
			m_tExplodeFrame.SetFrame(0, 25, 100);
		}
		break;

	case CORE_STATE::DEATH:

		if (m_tExplodeFrame.Frame())
		{
			OBJECT.AddObject(OBJKIND::EFFECT, new CExplode(m_tInfo.vPos
				+ Vector3(GetRand(-100, 100), GetRand(-100, 100), 0), 0))->GetInfo()->iDepth = 7;

			if (m_tExplodeFrame.CurFrame == m_tExplodeFrame.EndFrame)
			{
				m_iState = END_DEATH;
				OBJECT.AddUI(UIOBJKIND::SCREEN, new CBlackout([&]() {
					DATA.SetBackUpScene(SCENE.GetNowSceneName());
					SCENE.ChangeScene("S_GAMEOVER");
				}, 0));
			}
		}

		break;

	case CORE_STATE::END_DEATH:
		if (m_tExplodeFrame.Frame())
		{
			OBJECT.AddObject(OBJKIND::EFFECT, new CExplode(m_tInfo.vPos
				+ Vector3(GetRand(-100, 100), GetRand(-100, 100), 0), 0))->GetInfo()->iDepth = 7;
		}
		break;
	}

	m_tFrame.Frame();
}

void CCore::Render()
{
	IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos
	+ m_vOffset);
}

void CCore::Destroy()
{
	UNREGISTERCOLLIDER;
}

void CCore::OnCollision(CCollider * col)
{
}

void CCore::TakeDamage(float damage)
{
	m_fCurHp -= damage;

	D3DCOLORVALUE value = { 255,140,50,255 }; // 주황색

	if (damage < 0)
		value = { 50,255,140, 255 }; // 회복 ( 초록 )
	else if (damage >= 100)
		value = { 255,50,50,255 }; // 강한 데미지 ( 빨강 )

	auto hpUI = OBJECT.AddUI(UIOBJKIND::SCROLL,
		new CMoveText((damage > 0 ? "-" : "+") + to_string((int)abs(damage)),
			m_tInfo.vPos, value, Vector3(0, -20, 0), 2000, true, 70));
	hpUI->GetInfo()->iDepth = 11;

	if (m_fCurHp < 0)
		m_fCurHp = 0;
}