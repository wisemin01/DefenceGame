#pragma once
#include "CScene.h"
class CStage3 :
	public CScene
{
public:
	CStage3();
	~CStage3();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetDropPoints();
	void LoadWave();

	void AddBackground(CTexture* text, int iDepth, Vector3 vPos = V3CENTER);
	void AddCaust(Vector3 pos);
};

