#pragma once
#include "CObject.h"
class CCameraMover :
	public CObject
{
private:
	float m_fScreenX;
	float m_fScreenY;
	float m_fSpeed;

public:
	CCameraMover(float fScreenX, float fScreenY, float fSpeed);
	virtual ~CCameraMover();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

