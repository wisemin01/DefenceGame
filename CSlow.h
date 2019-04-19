#pragma once
#include "CObject.h"
class CSlow :
	public CObject
{
public:
	CSlow(Vector3 vPos, float size);
	~CSlow();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* col) override;
};

