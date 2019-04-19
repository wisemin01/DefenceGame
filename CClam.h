#pragma once
#include "CTower.h"
class CClam :
	public CTower
{
private:
	bool bPrevInCol = false;
public:
	CClam(Vector3 vPos);
	virtual ~CClam();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* _tCol) override;

	virtual void Upgrade() override;

public:
	void SetFrameAsRotation(Vector3 vDir);
	void SetFrameInIdle();
};

