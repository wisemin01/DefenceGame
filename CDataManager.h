#pragma once
#include "CSingleton.h"
class CDataManager :
	public CSingleton<CDataManager>
{
private:
	float m_fGold = 0;

	string m_sBackUpSceneCode;
public:
	CDataManager();
	virtual ~CDataManager();

	inline float GetGold() { return m_fGold; }
	inline void SetGold(float fSet) { m_fGold = fSet; }
	inline void AddGold(float fAdd) { m_fGold += fAdd; }

	inline string GetBackUpScene() { return m_sBackUpSceneCode; }
	inline void SetBackUpScene(const string& str) { m_sBackUpSceneCode = str; }
};

#define DATA (*CDataManager::GetInstance())