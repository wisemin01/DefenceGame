#pragma once
#include "CObject.h"
class CMoveText :
	public CObject
{
protected:
	string sText;
	Vector3 vVelocity;

	D3DCOLORVALUE colorValue;

	float fEndTime;
	float fSize;
	bool bIsDownAlpha = false;
	float fAlphaDown = 3;

public:
	CMoveText(const string& sText, Vector3 vPos, D3DCOLORVALUE colorValue,
		Vector3 vVel = Vector3(0, 0, 0), float fEnd = 0.0f, bool IsDownAlpha = false,
		float fFontSize = 50);
	~CMoveText();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetAlphaDownSpeed(float alphaDown) { fAlphaDown = alphaDown; }

};