#pragma once
#include "CTower.h"
class CSeaAnemone :
	public CTower
{
public:
	CSeaAnemone(Vector3 vPos);
	virtual ~CSeaAnemone();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* _tCol) override;

	virtual void Upgrade() override;
};

