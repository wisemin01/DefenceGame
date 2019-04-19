#pragma once
#include "CScene.h"
class CGameOverScene :
	public CScene
{
private:
	bool bEnd = false;
public:
	CGameOverScene();
	virtual ~CGameOverScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

