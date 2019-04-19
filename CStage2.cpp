#include "DXUT.h"
#include "CStage2.h"

#include "CObject.h"
#include "CBackground.h"
#include "CPopButton.h"
#include "CDropPoint.h"
#include "CEnemy.h"
#include "CEnemySpawn.h"
#include "CPrintGold.h"
#include "CCameraMover.h"
#include "CEffectSpawn.h"
#include "CCore.h"
#include "CGageBar.h"
#include "CBlackout.h"

#define STAGE_NUM 1

CStage2::CStage2()
{
}


CStage2::~CStage2()
{
}

void CStage2::Init()
{
	AddBackground(IMAGE.GetImage("STAGE2_BG"), -1, V3CENTER + Vector3(110, 0, 0));

	OBJECT.AddObject(OBJKIND::NORMAL, new CCameraMover(1500, 720, 600));
	OBJECT.AddUI(UIOBJKIND::SCREEN, new CEffectSpawn(1500, 720, 1));

	SetDropPoints();

	DATA.SetGold(400);
	SKILL.SetMana(0);
	SKILL.CreateButtons();

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 3; j++)
		{
			AddCaust(Vector3(160 + 320 * i, 160 + 320 * j, 0));
		}

	auto str = OBJECT.AddUI(UIOBJKIND::SCREEN, new CPrintGold());
	str->GetInfo()->iDepth = 10;

	OBJECT.AddObject(OBJKIND::CORE,
		new CCore(Vector3(1284.53, 211, 0), 500, IMAGE.GetImage("CORE2")));
	auto core2 = new CCore(Vector3(1291.53, 519, 0), 500, IMAGE.GetImage("CORE2"));
	core2->SetHpBarPos(Vector3(950, 30, 0));
	OBJECT.AddObject(OBJKIND::CORE, core2);
	core2->GetHpBar()->SetTexture("BIG_BAR2");

	auto moveText = new CMoveText("- STAGE 2 -",
		Vector3(WINSIZEX / 2, 200, 0), { 255,255,255,255 }, Vector3(0, -2, 0), 5000, true, 100);
	moveText->SetAlphaDownSpeed(0.5);
	OBJECT.AddUI(UIOBJKIND::SCREEN, moveText);

	OBJECT.AddUI(UIOBJKIND::SCREEN, new CBlackout([&]() { LoadWave(); }, 255));

}

void CStage2::Update()
{
}

void CStage2::Render()
{
}

void CStage2::Destroy()
{
}

void CStage2::SetDropPoints()
{
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(68, 52, 90, 90, 50));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(200, 52, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(720, 52, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(850, 52, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1100, 52, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1240, 52, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(330, 150, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(461, 150, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(594, 150, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(330, 248, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(68, 370, 90, 90, 50));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(330, 345, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(848, 345, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(977, 345, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1100, 345, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(68, 468, 90, 90, 50));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(595, 468, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(596, 572, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(333, 668, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(465, 668, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(728, 668, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(856, 668, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(987, 668, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1110, 668, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1240, 668, 90, 90, 0, false));

}

void CStage2::LoadWave()
{
	auto enemySpawn = new CEnemySpawn;

	string str[3] = { "SLIME","SLIME2","SOLDIER" };

	enemySpawn->InsertEnemy(5000, nullptr);

	for (int i = 0; i < 3; i++)
	{
		enemySpawn->CreateWave(STAGE_NUM, "- WAVE " + to_string(i + 1) + " -",
			20, 10000, 800 + i * 400, 18 + i * 3, 100 + i * 15,
			50 + i * 20, 950, i < 2 ? 9 : 11,
			IMAGE.GetImage(str[i]));
	}

	enemySpawn->CreateWave(STAGE_NUM, "- FINAL WAVE -",
		25, 10000, 2500, 30, 150, 100, 1200, 11, IMAGE.GetImage("SOLDIER"));

	OBJECT.AddObject(OBJKIND::SPAWN, enemySpawn);
}
void CStage2::AddBackground(CTexture * text, int iDepth, Vector3 vPos)
{
	auto bg = OBJECT.AddObject(OBJKIND::NORMAL, new CBackground);
	bg->SetTexture(text);
	bg->GetInfo()->vPos = vPos;
	bg->GetInfo()->iDepth = iDepth;
}

void CStage2::AddCaust(Vector3 pos)
{
	auto caust = OBJECT.AddUI(UIOBJKIND::SCROLL, new CObject);
	caust->GetInfo()->vPos = pos;
	caust->GetInfo()->vScale = Vector3(5, 5, 5);
	caust->GetInfo()->tColor = D3DCOLOR_ARGB(30, 255, 255, 255);
	caust->GetInfo()->iDepth = 5;
	caust->SetFrame(0, 31, 50);
	caust->SetTexture("CAUST");
}
