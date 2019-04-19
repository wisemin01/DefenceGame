#include "DXUT.h"
#include "CSkillManager.h"

#include "CPopButton.h"

#include "CDropBombs.h"
#include "CDropSlow.h"
#include "CEnemy.h"
#include "CMoveText.h"

CSkillManager::CSkillManager()
{
}


CSkillManager::~CSkillManager()
{
}

void CSkillManager::CreateButtons()
{
	OBJECT.AddUI(UIOBJKIND::SCREEN, new CPopButton(Vector3(50, WINSIZEY - 50, 0), IMAGE.GetImage("BTN_EXPLODE"), 75,
		75, [&]() {

		OBJECT.AddUI(UIOBJKIND::SCREEN, new CDropBombs(Vector2(400, 200)));

	}, true));

	OBJECT.AddUI(UIOBJKIND::SCREEN, new CPopButton(Vector3(140, WINSIZEY - 50, 0), IMAGE.GetImage("BTN_SLOW"), 75,
		75, [&]() {

		OBJECT.AddUI(UIOBJKIND::SCREEN, new CDropSlow(300));

	}, true));

	OBJECT.AddUI(UIOBJKIND::SCREEN, new CPopButton(Vector3(230, WINSIZEY - 50, 0), IMAGE.GetImage("BTN_TIME"), 75,
		75, [&]() {
		if (m_iMana >= 2) {
			for (auto iter : OBJECT.GetList(OBJKIND::ENEMY))
			{
				reinterpret_cast<CEnemy*>(iter)->SetSlow(4000, 0.0f);
			}
			m_iMana = 0;
		}
		else
		{
			auto hpUI = OBJECT.AddUI(UIOBJKIND::SCROLL,
				new CMoveText("There is not enough mana.",
					Vector3(WINSIZEX / 2, 200, 0),
					COLORVALUE_DEFAULT, Vector3(0, -10, 0), 2000, true, 75));

			hpUI->GetInfo()->iDepth = 11;
		}

	}, true));
}

void CSkillManager::Update()
{
	if (m_fFrameSkip <= GetNowTime())
	{
		if (m_iMana <= 9) {
			m_iMana += 1;
			m_fFrameSkip = GetNowTime() + 15000;
		}
	}
}
