#include "DXUT.h"
#include "CMaingame.h"

#include "CLoadingScene.h"
#include "CStage1.h"
#include "CStage2.h"
#include "CStage3.h"
#include "CGameOverScene.h"
#include "CClearScene.h"

CMaingame::CMaingame()
{
}


CMaingame::~CMaingame()
{
}

void CMaingame::Init()
{
	SCENE.AddScene("S_LOADING", new CLoadingScene);
	SCENE.AddScene("S_STAGE1" , new CStage1);
	SCENE.AddScene("S_STAGE2" , new CStage2);
	SCENE.AddScene("S_STAGE3" , new CStage3);
	SCENE.AddScene("S_GAMEOVER", new CGameOverScene);
	SCENE.AddScene("S_CLEAR", new CClearScene);


	SCENE.ChangeScene("S_LOADING");
}

void CMaingame::Update()
{
	INPUT.KeyUpdate();
	SCENE.Update();
	CAMERA.Update();

	SKILL.Update();

#if CHEET_MODE
	if (INPUT.GetKeyDown(VK_F1))
		SCENE.ChangeScene("S_STAGE1");
	if (INPUT.GetKeyDown(VK_F2))
		SCENE.ChangeScene("S_STAGE2");
	if (INPUT.GetKeyDown(VK_F3))
		SCENE.ChangeScene("S_STAGE3");

	if (INPUT.GetKeyDown(VK_SPACE))
	{
		Vector3 vMouse = INPUT.GetScrollMouse();
		CONSOLE_LOG(vMouse.x << ", " << vMouse.y);
	}
#endif
}

void CMaingame::Render()
{
	CAMERA.SetTranform();
	IMAGE.Begin(false);
	SCENE.Render();
	IMAGE.End();
}

void CMaingame::Destroy()
{
	CSceneManager::DestroyInstance();
	CInputManager::DestroyInstance();
	CObjectManager::DestroyInstance();
	CCameraManager::DestroyInstance();
	CImageManager::DestroyInstance();
	CDataManager::DestroyInstance();
	CSkillManager::DestroyInstance();
}

void CMaingame::ResetDevice()
{
	IMAGE.ResetDevice();
}

void CMaingame::LostDevice()
{
	IMAGE.LostDevice();
}
