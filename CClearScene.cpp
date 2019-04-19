#include "DXUT.h"
#include "CClearScene.h"

#include "CBlackout.h"
#include "CMoveText.h"


CClearScene::CClearScene()
{
}


CClearScene::~CClearScene()
{
}

void CClearScene::Init()
{
	OBJECT.AddUI(UIOBJKIND::SCREEN, new CBlackout([]() {}, 255));
	OBJECT.AddUI(UIOBJKIND::SCREEN, new CMoveText("- GAME CLEAR! -", V3CENTER, COLORVALUE_DEFAULT, V3ZERO, 0, 0, 100));
	OBJECT.AddUI(UIOBJKIND::SCREEN, new CMoveText("click to exit", V3CENTER + Vector3(0, 75, 0), COLORVALUE_DEFAULT, V3ZERO, 0, 0, 50));

	bEnd = false;
}

void CClearScene::Update()
{
	if (!bEnd && INPUT.GetKeyDown(VK_LBUTTON))
	{
		bEnd = true;
		OBJECT.AddUI(UIOBJKIND::SCREEN, new CBlackout([]() {PostQuitMessage(0); }, 0));
	}
}

void CClearScene::Render()
{
}

void CClearScene::Destroy()
{
}
