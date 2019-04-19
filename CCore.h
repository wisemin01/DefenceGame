#pragma once
#include "CObject.h"

class CGageBar;
class CCore
	: public CObject 
{
public:
	enum CORE_STATE
	{
		IDLE,
		DEATH,
		END_DEATH
	};
private:
	float m_fMaxHp;
	float m_fCurHp;

	Vector3 m_vOffset;
	Vector3 m_vHpBar;

	CGageBar* m_pMyHpBar;

	CFrame m_tExplodeFrame;

public:
	CCore(Vector3 vPos, float fHp, CTexture* pTex);
	~CCore();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* col) override;

	// HP �ٲܶ� �� ���
	// �ǰ� ������ ǥ�ñ�� & HP���� ����
	void TakeDamage(float damage);
	void SetHpBarPos(Vector3 vPos) { m_vHpBar = vPos; }
	CGageBar* GetHpBar() { return m_pMyHpBar; }
};

