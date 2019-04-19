#pragma once
#include "CObject.h"

enum BUTTON_STATE
{
	ON_IDLE,
	ON_MOUSE,
	ON_DOWN,
	ON_CLICK,
};

class CPopButton :
	public CObject
{
private:

	std::function<void()> m_pFunc;
	bool m_bIsScreen;

public:
	CPopButton(Vector3 vPos, CTexture* pText, float fWidth, float fHeight,
		std::function<void()> _pFunc, bool bIsScreen = false);
	virtual ~CPopButton();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	bool IsInside();
};

