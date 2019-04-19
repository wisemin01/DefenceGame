#include "DXUT.h"
#include "CSceneManager.h"

#include "CScene.h"

CSceneManager::CSceneManager()
{
}


CSceneManager::~CSceneManager()
{
	if (m_pNow)
		m_pNow->Destroy();
	for (auto iter : m_mapScenes)
	{
		SAFE_DELETE(iter.second);
	}
}

void CSceneManager::AddScene(const string & key, CScene * pScene)
{
	auto find = m_mapScenes.find(key);

	if (find == m_mapScenes.end())
	{
		m_mapScenes.insert(make_pair(key, pScene)); return;
	}

	MESSAGE_LOG((key + "이름을 가진 씬이 이미 존재합니다.").c_str());
}

CScene * CSceneManager::ChangeScene(const string & key)
{
	auto find = m_mapScenes.find(key);

	if (find != m_mapScenes.end())
	{
		m_pNext = find->second;
		m_sNowSceneCode = key;
		return m_pNext;
	}

	MESSAGE_LOG((key + "이름을 가진 씬이 없습니다.").c_str());
	return nullptr;
}

void CSceneManager::Update()
{
	if (m_pNext)
	{
		if (m_pNow)
		{
			m_pNow->Destroy();
			OBJECT.Destroy();
			CAMERA.SetPosition(V3CENTER);
		}

		m_pNext->Init();
		m_pNow = m_pNext;
		m_pNext = 0;

	}

	if (m_pNow)
	{
		m_pNow->Update();
		OBJECT.Update();
	}
}

void CSceneManager::Render()
{
	if (m_pNow) {
		m_pNow->Render();
		OBJECT.Render();
	}
}
