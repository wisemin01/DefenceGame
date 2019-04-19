#pragma once
#include "CBullet.h"
class CExplodeBullet :
	public CBullet
{
private:
	float m_fLifeTime;
public:
	CExplodeBullet(Vector3 vStart, Vector3 vDir, float size, float fSpeed, float fDamage, float fLifeTime);
	virtual ~CExplodeBullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* col) override;
};

