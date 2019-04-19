#pragma once
#include "CObject.h"
class CBlackout :
	public CObject
{
private:
	std::function<void()> m_pFunc;

	float m_fAlpha;
	bool m_bType;
public:
	CBlackout(function<void()> pFunc, float fStartAlpha);
	~CBlackout();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

