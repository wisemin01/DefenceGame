#pragma once
#include "CCollider.h"

class CInfo
{
public:
	Vector3 vPos;
	Vector3 vScale;
	string  sTag;

	unsigned long tColor = 0xffffffff;
	int iDepth = 0;
};

class CObject
{
protected:

	CTexture *  m_pTexture = nullptr;
	CCollider   m_tCollider;
	CInfo		m_tInfo;
	CFrame		m_tFrame;

	bool		m_bDelete  = false;
	int			m_iState = 0;

	int			m_iFlip = 1;

public:
	CObject() : m_tCollider(this) {}
	virtual ~CObject() {}

	virtual void Init	();
	virtual void Update	();
	virtual void Render	();
	virtual void Destroy();

	virtual void OnCollision(CCollider* tCol) {}

	void SetFrame(int iStart, int iEnd, DWORD dwDelay);
	void SetTexture(CTexture* pTexture);
	void SetTexture(const string& key);

	CInfo* GetInfo() { return &m_tInfo; }
	CFrame* GetFrame() { return &m_tFrame; }

	bool GetDelete() { return m_bDelete; }
	void SetDelete(bool flag) { m_bDelete = flag; }

	int GetState() { return m_iState; }
	void SetState(int iState) { m_iState = iState; }

	int GetFlip() { return m_iFlip; }
	void SetFlip(int iFlip) { m_iFlip = iFlip; }

public:

	static bool CompareDepth(CObject* _prev, CObject* _next)
	{
		return _prev->GetInfo()->iDepth < _next->GetInfo()->iDepth;
	}

	static bool CompareY(CObject* _prev, CObject* _next)
	{
		if (_prev->GetInfo()->iDepth == _next->GetInfo()->iDepth)
			return _prev->GetInfo()->vPos.y < _next->GetInfo()->vPos.y;
		else
			return false;
	}
};