#pragma once
#include "CSingleton.h"

class CScene;
class CSceneManager :
	public CSingleton<CSceneManager>
{
private:
	map<string, CScene*> m_mapScenes;

	CScene* m_pNow  = NULL;
	CScene* m_pNext = NULL;

	string m_sNowSceneCode;
public:
	CSceneManager();
	virtual ~CSceneManager();

	void AddScene(const string& key, CScene* pScene);
	CScene* ChangeScene(const string& key);

	void Update();
	void Render();

	string GetNowSceneName() { return m_sNowSceneCode; }
};

#define SCENE (*CSceneManager::GetInstance())