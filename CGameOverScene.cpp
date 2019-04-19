#include "DXUT.h"
#include "CGameOverScene.h"

#include "CBlackout.h"
#include "CMoveText.h"

CGameOverScene::CGameOverScene()
{
}


CGameOverScene::~CGameOverScene()
{
}

void CGameOverScene::Init()
{
	OBJECT.AddUI(UIOBJKIND::SCREEN, new CBlackout([]() {}, 255));
	OBJECT.AddUI(UIOBJKIND::SCREEN, new CMoveText("- GAME OVER -", V3CENTER, COLORVALUE_DEFAULT, V3ZERO, 0, 0, 100));
	OBJECT.AddUI(UIOBJKIND::SCREEN, new CMoveText("click to restart", V3CENTER + Vector3(0, 75, 0), COLORVALUE_DEFAULT, V3ZERO, 0, 0, 50));

	bEnd = false;
}

void CGameOverScene::Update()
{
	if (!bEnd && INPUT.GetKeyDown(VK_LBUTTON))
	{
		bEnd = true;
		OBJECT.AddUI(UIOBJKIND::SCREEN, new CBlackout([]() {SCENE.ChangeScene(DATA.GetBackUpScene());}, 0));
	}
}

void CGameOverScene::Render()
{
}

void CGameOverScene::Destroy()
{
}
