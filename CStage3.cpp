#include "DXUT.h"
#include "CStage3.h"

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
#include "CBlackout.h"

#define STAGE_NUM 2

CStage3::CStage3()
{
}


CStage3::~CStage3()
{
}

void CStage3::Init()
{
	AddBackground(IMAGE.GetImage("STAGE3_BG"), -1, V3CENTER + Vector3(320, 180, 0));

	OBJECT.AddObject(OBJKIND::NORMAL, new CCameraMover(1920, 1080, 600));
	OBJECT.AddUI(UIOBJKIND::SCREEN, new CEffectSpawn(1920, 1080, 2));

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 4; j++)
		{
			AddCaust(Vector3(160 + 320 * i, 160 + 320 * j, 0));
		}

	SetDropPoints();

	DATA.SetGold(500);
	SKILL.SetMana(0);
	SKILL.CreateButtons();

	auto str = OBJECT.AddUI(UIOBJKIND::SCREEN, new CPrintGold());
	str->GetInfo()->iDepth = 10;

	OBJECT.AddObject(OBJKIND::CORE,
		new CCore(Vector3(1781.05, 274, 0), 500, IMAGE.GetImage("CORE3")));

	auto moveText = new CMoveText("- STAGE 3 -",
		Vector3(WINSIZEX / 2, 200, 0), { 255,255,255,255 }, Vector3(0, -2, 0), 5000, true, 100);
	moveText->SetAlphaDownSpeed(0.5);
	OBJECT.AddUI(UIOBJKIND::SCREEN, moveText);

	OBJECT.AddUI(UIOBJKIND::SCREEN, new CBlackout([&]() { LoadWave(); }, 255));
}

void CStage3::Update()
{
}

void CStage3::Render()
{
}

void CStage3::Destroy()
{
}

void CStage3::SetDropPoints()
{
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(68, 51, 90, 90, 50));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(342, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(482, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(620, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(900, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1030, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1167, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1300, 51, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1580, 51, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1440, 186, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1580, 186, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(73, 300, 90, 90, 50));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(210, 300, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(490, 300, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1440, 300, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(210, 400, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(490, 400, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1030, 400, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1166, 400, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1444, 400, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(210, 500, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(350, 500, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(486, 500, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1030, 500, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1444, 500, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1580, 500, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(71, 610, 90, 90, 50));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1030, 610, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1845, 610, 90, 90, -50));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(71, 713, 90, 90, 50));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1032, 713, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1846, 713, 90, 90, -50));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(71, 815, 90, 90, 50));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1030, 815, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1847, 815, 90, 90, -50));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1030, 920, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1167, 920, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1846, 920, 90, 90, -50));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(71, 1024, 90, 90, 50, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(207, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(343, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(483, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(622, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(754, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(890, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1300, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1440, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1570, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1710, 1024, 90, 90, 0, false));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1846, 1024, 90, 90, -50, false));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(351, 746, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(487, 746, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(621, 746, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(761, 746, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(759, 226, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(759, 330, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(759, 435, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(759, 540, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(759, 640, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1306, 630, 90, 90));

	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1444, 739, 90, 90));
	OBJECT.AddObject(OBJKIND::DROP_POINT, new CDropPoint(1576, 739, 90, 90));

}

void CStage3::LoadWave()
{
	auto enemySpawn = new CEnemySpawn;

	string str[3] = { "SLIME","SLIME2","SOLDIER" };

	enemySpawn->InsertEnemy(5000, nullptr);

	for (int i = 0; i < 4; i++)
	{
		enemySpawn->CreateWave(STAGE_NUM, "- WAVE " + to_string(i + 1) + " -",
			25, 15000, 900 + i * 600, 15 + i * 2, 125 + i * 10,
			50 + i * 20, 900, i < 2 ? 9 : 11,
			IMAGE.GetImage(i <= 2 ? str[i] : str[2]));
	}

	enemySpawn->CreateWave(STAGE_NUM, "- FINAL WAVE -",
		30, 10000, 4200, 25, 180, 95, 1000, 9, IMAGE.GetImage("SLIME2"));

	OBJECT.AddObject(OBJKIND::SPAWN, enemySpawn);
}

void CStage3::AddBackground(CTexture * text, int iDepth, Vector3 vPos)
{
	auto bg = OBJECT.AddObject(OBJKIND::NORMAL, new CBackground);
	bg->SetTexture(text);
	bg->GetInfo()->vPos = vPos;
	bg->GetInfo()->iDepth = iDepth;
}

void CStage3::AddCaust(Vector3 pos)
{
	auto caust = OBJECT.AddUI(UIOBJKIND::SCROLL, new CObject);
	caust->GetInfo()->vPos = pos;
	caust->GetInfo()->vScale = Vector3(5, 5, 5);
	caust->GetInfo()->tColor = D3DCOLOR_ARGB(30, 255, 255, 255);
	caust->GetInfo()->iDepth = 5;
	caust->SetFrame(0, 31, 50);
	caust->SetTexture("CAUST");
}
