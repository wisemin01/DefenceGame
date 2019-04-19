#include "DXUT.h"
#include "CDropPoint.h"

#include "CPopButton.h"
#include "CTower.h"
#include "CMoveText.h"
#include "CClam.h"
#include "CCoral.h"
#include "CSeaAnemone.h"
#include "CTexture.h"


CDropPoint::CDropPoint(float x, float y, float width, float height, float fOffsetX, bool buttonSet)
	:m_fOffsetX(fOffsetX), m_bButtonSet(buttonSet)
{
	m_tInfo.vPos = Vector3(x, y, 0);
	m_tCollider.SetCollider(width, height);
	m_tInfo.iDepth = 1;
}

CDropPoint::~CDropPoint()
{
}

void CDropPoint::Init()
{
	for (int i = 0; i < 3; i++)
		m_pButton[i] = nullptr;

	m_pTexture = IMAGE.GetImage("ARROW");
	m_tFrame.SetFrame(0, 4, 180);
}

void CDropPoint::Update()
{
	bool bIsOnMouse = m_tCollider.IsInside(INPUT.GetScrollMouse());

	if (INPUT.GetKeyDown(VK_LBUTTON))
	{
		if (bIsOnMouse)
		{
			OpenButtons();
		}
		else
		{
			if (!IsMouseOnButtons())
				CloseButtons();
		}
	}
	m_tFrame.Frame();
}

void CDropPoint::Render()
{
	if (m_bIsSelected)
		IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos
			+ Vector3(0, -50, 0));
}

void CDropPoint::Destroy()
{
}

void CDropPoint::OpenButtons()
{
	float Y_offSet = m_bButtonSet ? 100 : -100;

	if (!m_pTower)
	{
		m_bIsSelected = true;
		// 타워가 없을 때
		// 첫번째 타워 설치, 두번째 타워 설치, 세번째 타워 설치
		if (!m_pButton[0])
		{
			m_pButton[0] = new CPopButton(m_tInfo.vPos
				+ Vector3(m_fOffsetX + -80, Y_offSet, 0), IMAGE.GetImage("BTN_CLAM"), 75, 75,
				[&]() {
				if (CTower::IsCanDrop(DATA.GetGold(), TOWER_KIND::CLAM))
				{
					m_pTower = new CClam(m_tInfo.vPos);
					OBJECT.AddObject(OBJKIND::TOWER, m_pTower);
					CloseButtons();
				}
				else
				{
					CloseButtons();
				}
			});
			OBJECT.AddUI(UIOBJKIND::SCROLL, m_pButton[0]);
			m_pButton[0]->GetInfo()->vScale = Vector3(0, 0, 0);
		}
		if (!m_pButton[1]) {
			m_pButton[1] = new CPopButton(m_tInfo.vPos
				+ Vector3(m_fOffsetX, Y_offSet, 0), IMAGE.GetImage("BTN_CORAL"), 75, 75,
				[&]() {
				if (CTower::IsCanDrop(DATA.GetGold(), TOWER_KIND::CORAL))
				{
					m_pTower = new CCoral(m_tInfo.vPos);
					OBJECT.AddObject(OBJKIND::TOWER, m_pTower);
					CloseButtons();
				}
				else
				{
					CloseButtons();
				}
			});
			OBJECT.AddUI(UIOBJKIND::SCROLL, m_pButton[1]);
			m_pButton[1]->GetInfo()->vScale = Vector3(0, 0, 0);
		}
		if (!m_pButton[2]) {
			m_pButton[2] = new CPopButton(m_tInfo.vPos
				+ Vector3(m_fOffsetX + 80, Y_offSet, 0), IMAGE.GetImage("BTN_ANEMONE"), 75, 75,
				[&]() {
				if (CTower::IsCanDrop(DATA.GetGold(), TOWER_KIND::SEA_ANEMONE))
				{
					m_pTower = new CSeaAnemone(m_tInfo.vPos);
					OBJECT.AddObject(OBJKIND::TOWER, m_pTower);
					CloseButtons();
				}
				else
				{
					CloseButtons();
				}
			});
			OBJECT.AddUI(UIOBJKIND::SCROLL, m_pButton[2]);
			m_pButton[2]->GetInfo()->vScale = Vector3(0, 0, 0);
		}

	}

	else

	{
		// 타워가 있을 때
		// 업그레이드, 판매

		if (!m_pButton[0]) {
			m_pButton[0] = new CPopButton(m_tInfo.vPos
				+ Vector3(m_fOffsetX - 40, Y_offSet, 0), IMAGE.GetImage("BTN_UPGRADE"), 75, 75,
				[&]() {
				// 업그레이드
				if (m_pTower->IsCanUpgrade())
				{
					m_pTower->Upgrade();
				}
				CloseButtons();
			});
			OBJECT.AddUI(UIOBJKIND::SCROLL, m_pButton[0]);
			m_pButton[0]->GetInfo()->vScale = Vector3(0, 0, 0);
		}
		if (!m_pButton[1]) {
			m_pButton[1] = new CPopButton(m_tInfo.vPos
				+ Vector3(m_fOffsetX + 40, Y_offSet, 0), IMAGE.GetImage("BTN_SELL"), 75, 75,
				[&]() {
				m_pTower->Sell();
				m_pTower = nullptr;
				CloseButtons();
			});
			OBJECT.AddUI(UIOBJKIND::SCROLL, m_pButton[1]);
			m_pButton[1]->GetInfo()->vScale = Vector3(0, 0, 0);
		}
	}
}

void CDropPoint::CloseButtons()
{
	for (int i = 0; i < 3; i++)
	{
		if (m_pButton[i]) {
			m_pButton[i]->SetDelete(true);
			m_pButton[i] = nullptr;
		}
	}
	m_bIsSelected = false;
}

bool CDropPoint::IsMouseOnButtons()
{
	for (int i = 0; i < 3; i++)
	{
		if (m_pButton[i] && m_pButton[i]->IsInside())
			return true;
	}
	return false;
}
