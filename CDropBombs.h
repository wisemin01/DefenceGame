#pragma once
#include "CObject.h"
class CDropBombs :
	public CObject
{
private:
	enum SKILL_STATE
	{
		ON_MOUSE,
		DROPED
	};
private:
	float width;
	float height;

public:
	CDropBombs(Vector2 vSize);
	~CDropBombs();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

