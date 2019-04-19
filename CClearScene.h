#pragma once
#include "CScene.h"
class CClearScene :
	public CScene
{
	bool bEnd;
public:
	CClearScene();
	~CClearScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

