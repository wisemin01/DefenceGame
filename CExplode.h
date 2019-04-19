#pragma once
#include "CObject.h"
class CExplode :
	public CObject
{
private:
	float fDamage;
	bool endAttack;
public:
	CExplode(Vector3 vPos, float Damage);
	~CExplode();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* _tCol) override;
};

