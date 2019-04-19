#include "DXUT.h"
#include "CDropBombs.h"

#include "CExplodeBullet.h"
#include "CMoveText.h"

CDropBombs::CDropBombs(Vector2 vSize)
	: width(vSize.x), height(vSize.y)
{
	m_tInfo.vPos = INPUT.GetScreenMouse();
}

CDropBombs::~CDropBombs()
{
}

void CDropBombs::Init()
{
	m_tFrame.SetFrame(0, 20, 90);
	m_tInfo.iDepth = -2;
	m_iState = ON_MOUSE;
}

void CDropBombs::Update()
{
	switch (m_iState) {

	case ON_MOUSE:
		m_tInfo.vPos = INPUT.GetScreenMouse();

		if (INPUT.GetKeyDown(VK_LBUTTON))
		{
			if (SKILL.GetMana() >= 2)
			{
				SKILL.AddMana(-2);

				m_iState = DROPED;
				m_tInfo.vPos = INPUT.GetScrollMouse();
			}
			else
			{
				auto hpUI = OBJECT.AddUI(UIOBJKIND::SCROLL,
					new CMoveText("There is not enough mana.",
						Vector3(WINSIZEX / 2, 200, 0),
						COLORVALUE_DEFAULT, Vector3(0, -10, 0), 2000, true, 75));
				
				hpUI->GetInfo()->iDepth = 11;
				SetDelete(true);
			}
		}
		if (INPUT.GetKeyDown(VK_RBUTTON))
		{
			SetDelete(true);
		}
		break;

	case DROPED:

		if (m_tFrame.Frame())
		{
			Vector3 TargetVec = m_tInfo.vPos + Vector3(GetRand(-width / 2, width / 2), GetRand(-height / 4, height / 4), 0);
			Vector3 StartVec = TargetVec + Vector3(GetRand(-50, 50), -240, 0);
			Vector3 Dir = TargetVec - StartVec;

			D3DXVec3Normalize(&Dir, &Dir);
			OBJECT.AddObject(OBJKIND::BULLET, new CExplodeBullet(
				StartVec, Dir, 10, 1500, GetRand(25, 150), 195));

			if (m_tFrame.CurFrame == m_tFrame.EndFrame)
			{
				SetDelete(true);
			}
		}

		break;
	}
}

void CDropBombs::Render()
{
	Vector2 vert[5];
	Vector3 vPos = m_tInfo.vPos;

	vert[0] = Vector2(vPos) + Vector2(-width / 2.f, -height / 2.f);
	vert[1] = Vector2(vPos) + Vector2(width / 2.f, -height / 2.f);
	vert[2] = Vector2(vPos) + Vector2(width / 2.f, height / 2.f);
	vert[3] = Vector2(vPos) + Vector2(-width / 2.f, height / 2.f);
	vert[4] = vert[0];

	if (m_iState == ON_MOUSE)
		IMAGE.DrawLine(vert, 5, 15, 0, D3DCOLOR_ARGB(100, 255, 75, 75));
	//else
	//	IMAGE.DrawLine(vert, 5, 15, 0, D3DCOLOR_ARGB(200, 120, 75, 75));
}

void CDropBombs::Destroy()
{
}
