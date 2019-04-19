#include "DXUT.h"
#include "CDropSlow.h"

#include "CEnemy.h"
#include "CTexture.h"
#include "CSlow.h"
#include "CMoveText.h"

CDropSlow::CDropSlow(float size)
	:size(size)
{
}

CDropSlow::~CDropSlow()
{
}

void CDropSlow::Init()
{
	m_tInfo.iDepth = -2;
	m_iState = ON_MOUSE;

	m_tCollider.SetCollider(size);
}

void CDropSlow::Update()
{
	m_tInfo.vPos = INPUT.GetScreenMouse();

	if (INPUT.GetKeyDown(VK_LBUTTON))
	{
		if (SKILL.GetMana() >= 2)
		{
			SKILL.AddMana(-2);

			OBJECT.AddObject(OBJKIND::EFFECT, new CSlow(INPUT.GetScrollMouse(), 300));
			SetDelete(true);
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
}

void CDropSlow::Render()
{
	Vector2 vert[5];
	Vector3 vPos = m_tInfo.vPos;

	vert[0] = Vector2(vPos) + Vector2(-size / 2.f, -size / 2.f);
	vert[1] = Vector2(vPos) + Vector2(size / 2.f, -size / 2.f);
	vert[2] = Vector2(vPos) + Vector2(size / 2.f, size / 2.f);
	vert[3] = Vector2(vPos) + Vector2(-size / 2.f, size / 2.f);
	vert[4] = vert[0];

	IMAGE.DrawLine(vert, 5, 15, 0, D3DCOLOR_ARGB(100, 255, 75, 75));
}


void CDropSlow::Destroy()
{
}

void CDropSlow::OnCollision(CCollider * col)
{

}
