#pragma once
#include "CObject.h"

class CTower;
class CPopButton;

class CDropPoint :
	public CObject
{
private:
	CTower * m_pTower = nullptr;

	CPopButton* m_pButton[3] = { nullptr };

	float m_fOffsetX;

	bool m_bButtonSet;
	bool m_bIsSelected = false;
public:
	CDropPoint(float x, float y, float width, float height, float fOffsetX = 0, bool buttonSet = true);
	virtual ~CDropPoint();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

public:
	void OpenButtons();
	void CloseButtons();

	bool IsMouseOnButtons();
};

