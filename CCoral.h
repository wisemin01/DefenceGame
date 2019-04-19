#pragma once
#include "CTower.h"

class CCoral :
	public CTower
{
protected:

public:
	CCoral(Vector3 vPos);
	~CCoral();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* _tCol) override;

	virtual void Upgrade() override;
};

