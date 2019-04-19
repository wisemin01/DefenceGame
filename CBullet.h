#pragma once
#include "CObject.h"
class CBullet :
	public CObject
{
protected:
	Vector3 m_vDirection;
	float m_fSpeed;
	float m_fDamage;

	float m_fRot;
public:
	CBullet(Vector3 vStart, Vector3 vDir, float size, float fSpeed, float fDamage);
	virtual ~CBullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* _tCol) override;
};

