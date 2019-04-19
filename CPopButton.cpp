#include "DXUT.h"
#include "CPopButton.h"

#include "CTexture.h"

CPopButton::CPopButton(Vector3 vPos, CTexture * pText, float fWidth,
	float fHeight, std::function<void()> _pFunc, bool bIsScreen)
	: m_bIsScreen(bIsScreen)
{
	m_tInfo.vPos = vPos;
	m_pTexture = pText;
	m_tCollider.SetCollider(fWidth, fHeight);
	m_tInfo.vScale = Vector3(1, 1, 1);
	m_pFunc = _pFunc;
}


CPopButton::~CPopButton()
{
}

void CPopButton::Init()
{
	m_tInfo.iDepth = 10;
}

void CPopButton::Update()
{
	bool bInside = IsInside();

	if (bInside)
	{
		if (m_iState == ON_IDLE || m_iState == ON_CLICK)
			m_iState = ON_MOUSE;
	}
	else
		m_iState = ON_IDLE;

	if (INPUT.GetKeyPress(VK_LBUTTON))
	{
		if (bInside) 
			m_iState = ON_DOWN;
		else
			m_iState = ON_IDLE;
	}

	if (m_iState == ON_DOWN)
		if (INPUT.GetKeyUp(VK_LBUTTON))
		{
			if (bInside) {
				m_pFunc();
				m_iState = ON_CLICK;
			}
		}

	if (m_iState == ON_MOUSE)
		Lerp(&m_tInfo.vScale, m_tInfo.vScale, Vector3(1.2, 1.2, 1.2), 7 * DXUTGetElapsedTime());
	else
		Lerp(&m_tInfo.vScale, m_tInfo.vScale, Vector3(1.0, 1.0, 1.0), 7 * DXUTGetElapsedTime());
}

void CPopButton::Render()
{
	IMAGE.ScaleRender(m_pTexture->GetImage(m_iState == ON_CLICK ? ON_IDLE : m_iState), m_tInfo.vPos, m_tInfo.vScale);
}

void CPopButton::Destroy()
{
}

bool CPopButton::IsInside()
{
	bool result;

	if (m_bIsScreen)
		result = m_tCollider.IsInside(INPUT.GetScreenMouse());
	else
		result = m_tCollider.IsInside(INPUT.GetScrollMouse());

	return result;
}