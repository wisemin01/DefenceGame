#pragma once
#include "CObject.h"
class CDropSlow :
	public CObject
{
private:
	enum SKILL_STATE
	{
		ON_MOUSE,
		DROPED
	};
	float size;
public:
	CDropSlow(float size);
	~CDropSlow();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* col) override;
};

