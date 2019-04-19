#pragma once
#include "CSingleton.h"
class CSkillManager :
	public CSingleton<CSkillManager>
{
private:
	int m_iMana;
	float m_fFrameSkip;
public:
	CSkillManager();
	~CSkillManager();

	void CreateButtons();
	void Update();

	int GetMana() { return m_iMana; }
	void AddMana(int iMana) { m_iMana += iMana; }
	void SetMana(int iMana) { m_iMana = iMana; }
};

#define SKILL (*CSkillManager::GetInstance())