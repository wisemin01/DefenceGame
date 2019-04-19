#pragma once
#include "CScene.h"
class CLoadingScene :
	public CScene
{
private:
	struct strBun
	{
		string key;
		string path;
		int count;
		strBun(const string& _key, const string& _path, int _count)
			: key(_key), path(_path), count(_count) {}
	};

	vector<strBun> m_sLoading;

	int m_iCurLoad;
	int m_iMaxLoad;

	CTexture* m_pBlackout;

public:
	CLoadingScene();
	virtual ~CLoadingScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetEnemyLoad();

	void Load(const string& key, const string& path, int count = 0) { m_sLoading.push_back(strBun(key, path, count)); }
};

