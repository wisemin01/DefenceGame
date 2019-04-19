#include "DXUT.h"
#include "CStage1.h"

#include "CObject.h"
#include "CBackground.h"
#include "CPopButton.h"
#include "CDropPoint.h"
#include "CEnemy.h"
#include "CEnemySpawn.h"
#include "CPrintGold.h"
#include "CEffectSpawn.h"
#include "CCore.h"
#include "CBlackout.h"
#include "CDropBombs.h"

#define STAGE_NUM 0

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Init()
{
	AddBackground(IMAGE.GetImage("STAGE1_BG", 0), -3);
	AddBackground(IMAGE.GetImage("STAGE1_BG", 1), -3);
	AddBackground(IMAGE.GetImage("STAGE1_BG", 2), -1);
	AddBackground(IMAGE.GetImage("STAGE1_BG", 3), 3);

	AddBackground(IMAGE.GetImage("STAGE1_HOUSE", 0), 0, Vector3(717, 275, 0));
	AddBackground(IMAGE.GetImage("STAGE1_HOUSE", 1), 0, Vector3(429, 453, 0));
	AddBackground(IMAGE.GetImage("STAGE1_HOUSE", 2), 0, Vector3(951, 461, 0));

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			AddCaust(Vector3(160 + 320 * i, 160 + 320 * j, 0));
		}

	OBJECT.AddUI(UIOBJKIND::SCREEN, new CEffectSpawn(1280, 720, 0));

	OBJECT.AddObject(OBJKIND::CORE,
		new CCore(Vector3(1100, 620, 0), 500, IMAGE.GetImage("CORE1")));

	auto str = OBJECT.AddUI(UIOBJKIND::SCREEN, new CPrintGold());
	str->GetInfo()->iDepth = 10;

	DATA.SetGold(300);
	SKILL.SetMana(0);
	SKILL.CreateButtons();

	SetDropPoints();

	auto moveText = new CMoveText("- STAGE 1 -",
		Vector3(WINSIZEX / 2, 200, 0), { 255,255,255,255 }, Vector3(0, -2, 0), 5000, true, 100);
	moveText->SetAlphaDownSpeed(0.5);
	OBJECT.AddUI(UIOBJKIND::SCREEN, moveText);

	OBJECT.AddUI(UIOBJKIND::SCREEN, new CBlackout([&]() {
		LoadWave();
	}, 255));
}

void CStage1::Update()
{
	if (INPUT.GetKeyDown(VK_TAB))
	{
		OBJECT.AddObject(OBJKIND::SPAWN, new CDropBombs(Vector2(400, 200)));
	}
}

void CStage1::Render()
{
}

void CStage1::Destroy()
{

}

void CStage1::SetDropPoints()
{
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(67, 51, 90, 90, 50));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(330, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(462, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(591, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(721, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(853, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(986, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1114, 51, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(67, 252, 90, 90, 50));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(198, 252, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(330, 252, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(460, 252, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(592, 252, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(854, 252, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(985, 252, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(296, 444, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(558, 444, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(689, 444, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(822, 444, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1083, 444, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1212, 444, 90, 90, -50));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(200, 673, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(461, 673, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(592, 673, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(723, 673, 90, 90, 0, false));
}

void CStage1::LoadWave()
{
	auto enemySpawn = new CEnemySpawn;

	string str[3] = { "SLIME","SLIME2","SOLDIER" };

	enemySpawn->InsertEnemy(5000, nullptr);

	for (int i = 0; i < 3; i++)
	{
		enemySpawn->CreateWave(STAGE_NUM, "- WAVE " + to_string(i + 1) + " -",
			20, 10000, 800 + i * 250, 18 + i * 3, 100 + i * 12,
			50 + i * 15, 1000, i < 2 ? 9 : 11,
			IMAGE.GetImage(str[i]));
	}

	enemySpawn->CreateWave(STAGE_NUM, "- FINAL WAVE -",
		20, 10000, 2000, 35, 140, 90, 1000, 11, IMAGE.GetImage("SOLDIER"));

	OBJECT.AddObject(OBJKIND::SPAWN, enemySpawn);
}

void CStage1::AddBackground(CTexture * text, int iDepth, Vector3 vPos)
{
	auto bg = OBJECT.AddObject(OBJKIND::NORMAL, new CBackground);
	bg->SetTexture(text);
	bg->GetInfo()->vPos = vPos;
	bg->GetInfo()->iDepth = iDepth;
}

void CStage1::AddCaust(Vector3 pos)
{
	auto caust = OBJECT.AddUI(UIOBJKIND::SCROLL, new CObject);
	caust->GetInfo()->vPos = pos;
	caust->GetInfo()->vScale = Vector3(5, 5, 5);
	caust->GetInfo()->tColor = D3DCOLOR_ARGB(30, 255, 255, 255);
	caust->GetInfo()->iDepth = 5;
	caust->SetFrame(0, 31, 50);
	caust->SetTexture("CAUST");
}
