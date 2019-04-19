#include "DXUT.h"
#include "CInputManager.h"


CInputManager::CInputManager()
{
	memset(m_bKeyState, 0, sizeof(m_bKeyState));
	memset(m_bOldState, 0, sizeof(m_bKeyState));
}


CInputManager::~CInputManager()
{
}

void CInputManager::KeyUpdate()
{
	for (int i = 0; i < 256; i++)
	{
		m_bOldState[i] = m_bKeyState[i];
		m_bKeyState[i] = bool(GetAsyncKeyState(i));
	}
}

bool CInputManager::GetKeyDown(int iType)
{
	return m_bOldState[iType] == false && m_bKeyState[iType] == true;
}

bool CInputManager::GetKeyUp(int iType)
{
	return m_bOldState[iType] == true && m_bKeyState[iType] == false;
}

bool CInputManager::GetKeyPress(int iType)
{
	return m_bOldState[iType] && m_bKeyState[iType];
}

Vector3 CInputManager::GetScreenMouse()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	Vector3 ret(pt.x, pt.y, 0);

	return ret;
}

Vector3 CInputManager::GetScrollMouse()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	Vector3 ret(pt.x - WINSIZEX / 2, pt.y - WINSIZEY / 2, 0);
	ret += CAMERA.GetPosition();

	return ret;
}
