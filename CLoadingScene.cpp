#include "DXUT.h"
#include "CLoadingScene.h"

#include "CEnemy.h"
#include "CTower.h"
#include "CBlackout.h"

CLoadingScene::CLoadingScene()
{
}


CLoadingScene::~CLoadingScene()
{
}

void CLoadingScene::Init()
{
	m_iCurLoad = 0;


	Load("BULLET", "./Resource/Dummy/Bullet.png");
	Load("EXPLODE", "./Resource/Dummy/Explode/%d.png", 6);
	Load("SLOW", "./Resource/Effects/slow/Slow(%d).png", 11);

	Load("BTN_CLAM", "./Resource/UI/CLAM%d.png", 3);
	Load("BTN_CORAL", "./Resource/UI/CORAL%d.png", 3);
	Load("BTN_ANEMONE", "./Resource/UI/ANEMONE%d.png", 3);
	Load("BTN_SELL", "./Resource/UI/SELL%d.png", 3);
	Load("BTN_UPGRADE", "./Resource/UI/UPGRADE%d.png", 3);
	Load("BTN_TIME", "./Resource/UI/TIME%d.png", 3);
	Load("BTN_EXPLODE", "./Resource/UI/EXPLODE%d.png", 3);
	Load("BTN_SLOW", "./Resource/UI/SLOW%d.png", 3);


	Load("BIG_FISH", "./Resource/Effects/BigFish.png");
	Load("SMALL_FISH", "./Resource/Effects/SmallFish.png");
	Load("BUBBLE", "./Resource/Effects/Bubble.png");

	Load("STAGE1_BG", "./Resource/Stage1/%d.png", 4);
	Load("STAGE1_HOUSE", "./Resource/Stage1/house%d.png", 3);

	Load("STAGE2_BG", "./Resource/Stage2/%d.png", 3);
	Load("STAGE3_BG", "./Resource/Stage3/%d.png", 2);

	Load("CLAM1", "./Resource/Tower/Clam1/Clam(%d).png", 128);
	Load("CLAM2", "./Resource/Tower/Clam2/Clam(%d).png", 128);
	Load("CLAM3", "./Resource/Tower/Clam3/Clam(%d).png", 128);

	Load("CORAL1", "./Resource/Tower/Coral1/Coral(%d).png", 11);
	Load("CORAL2", "./Resource/Tower/Coral2/Coral(%d).png", 11);
	Load("CORAL3", "./Resource/Tower/Coral3/Coral(%d).png", 11);

	Load("SEA_ANEMONE1", "./Resource/Tower/SeaAnemone1/Anemone(%d).png", 11);
	Load("SEA_ANEMONE2", "./Resource/Tower/SeaAnemone2/Anemone(%d).png", 11);
	Load("SEA_ANEMONE3", "./Resource/Tower/SeaAnemone3/Anemone(%d).png", 11);

	Load("SLIME", "./Resource/Enemy/Slime/Slime(%d).png", 45);
	Load("SLIME2", "./Resource/Enemy/Slime/Slime2(%d).png", 45);
	Load("SOLDIER", "./Resource/Enemy/Soldier/Soldier(%d).png", 55);

	Load("CAUST", "./Resource/Effects/Caust/(%d).png", 32);
	Load("ARROW", "./Resource/Arrow/Arrow(%d).png", 5);

	Load("CORE1", "./Resource/Core/1/Core(%d).png", 11);
	Load("CORE2", "./Resource/Core/2/Core(%d).png", 11);
	Load("CORE3", "./Resource/Core/3/Core(%d).png", 11);

	Load("SMALL_BAR", "./Resource/UI/ENEMYHP%d.png", 2);
	Load("BIG_BAR", "./Resource/UI/PLAYERHP%d.png", 2);
	Load("BIG_BAR2", "./Resource/UI/BOSSHP%d.png", 2);

	Load("BLUE_BULLET", "./Resource/Effects/Bullet/1(%d).png", 3);
	Load("BLACK_BULLET", "./Resource/Effects/Bullet/2(%d).png", 3);

	Load("BLACK", "./Resource/Effects/Black.png");

	m_iMaxLoad = m_sLoading.size();

	SetEnemyLoad();
	CTower::SetTowerInfo();
}

void CLoadingScene::Update()
{
	if (m_iCurLoad != m_iMaxLoad) {

		IMAGE.AddImage(m_sLoading[m_iCurLoad].key,
			m_sLoading[m_iCurLoad].path, m_sLoading[m_iCurLoad].count);

		m_iCurLoad++;

		if (m_iCurLoad == m_iMaxLoad)
			OBJECT.AddUI(UIOBJKIND::SCREEN,
				new CBlackout([&]() {SCENE.ChangeScene("S_STAGE1"); }, 0));
	}
}

void CLoadingScene::Render()
{
	IMAGE.PrintCenterText(to_string(
		(int)(((float)m_iCurLoad / (float)m_iMaxLoad) * 100)) + "%"
		, WINSIZEX / 2, WINSIZEY / 2, 100, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLoadingScene::Destroy()
{
}

void CLoadingScene::SetEnemyLoad()
{
	std::vector<Vector3> stage1Load;

	stage1Load.push_back(Vector3(0, 165, 0));
	stage1Load.push_back(Vector3(1174, 165, 0));
	stage1Load.push_back(Vector3(1205, 255, 0));
	stage1Load.push_back(Vector3(1200, 325, 0));
	stage1Load.push_back(Vector3(1155, 354, 0));
	stage1Load.push_back(Vector3(92, 354, 0));
	stage1Load.push_back(Vector3(68, 450, 0));
	stage1Load.push_back(Vector3(100, 562, 0));
	stage1Load.push_back(Vector3(834, 562, 0));
	stage1Load.push_back(Vector3(1280, 620, 0));

	CEnemy::SetEnemyLoad(stage1Load, 0, 0);

	std::vector<Vector3> stage2Load_1, stage2Load_2;

	stage2Load_1.push_back(Vector3(0, 179, 0));
	stage2Load_1.push_back(Vector3(184, 179, 0));
	stage2Load_1.push_back(Vector3(207, 537, 0));
	stage2Load_1.push_back(Vector3(446, 540, 0));
	stage2Load_1.push_back(Vector3(462, 300, 0));
	stage2Load_1.push_back(Vector3(710, 300, 0));
	stage2Load_1.push_back(Vector3(730, 200, 0));
	stage2Load_1.push_back(Vector3(1200, 200, 0));

	stage2Load_2.push_back(Vector3(0, 179, 0));
	stage2Load_2.push_back(Vector3(184, 179, 0));
	stage2Load_2.push_back(Vector3(207, 537, 0));
	stage2Load_2.push_back(Vector3(446, 540, 0));
	stage2Load_2.push_back(Vector3(462, 300, 0));
	stage2Load_2.push_back(Vector3(710, 300, 0));
	stage2Load_2.push_back(Vector3(730, 511, 0));
	stage2Load_2.push_back(Vector3(1200, 511, 0));

	CEnemy::SetEnemyLoad(stage2Load_1, 1, 0);
	CEnemy::SetEnemyLoad(stage2Load_2, 1, 1);

	std::vector<Vector3> stage3Load;

	stage3Load.push_back(Vector3(10, 195, 0));
	stage3Load.push_back(Vector3(619, 199, 0));
	stage3Load.push_back(Vector3(621, 649, 0));
	stage3Load.push_back(Vector3(213, 653, 0));
	stage3Load.push_back(Vector3(218, 908, 0));
	stage3Load.push_back(Vector3(888, 902, 0));
	stage3Load.push_back(Vector3(902, 262, 0));
	stage3Load.push_back(Vector3(1298, 247, 0));
	stage3Load.push_back(Vector3(1299, 525, 0));
	stage3Load.push_back(Vector3(1168, 538, 0));
	stage3Load.push_back(Vector3(1165, 791, 0));
	stage3Load.push_back(Vector3(1297, 808, 0));
	stage3Load.push_back(Vector3(1305, 893, 0));
	stage3Load.push_back(Vector3(1703, 897, 0));
	stage3Load.push_back(Vector3(1710, 506, 0));
	stage3Load.push_back(Vector3(1780, 312, 0));

	CEnemy::SetEnemyLoad(stage3Load, 2, 0);
}