#pragma once
#include "CSingleton.h"
class CInputManager :
	public CSingleton<CInputManager>
{
private:
	bool m_bKeyState[256];
	bool m_bOldState[256];
public:
	CInputManager();
	virtual ~CInputManager();

	void KeyUpdate();

	bool GetKeyDown(int iType);
	bool GetKeyUp(int iType);
	bool GetKeyPress(int iType);

	Vector3 GetScreenMouse();
	Vector3 GetScrollMouse();
};

#define INPUT (*CInputManager::GetInstance())