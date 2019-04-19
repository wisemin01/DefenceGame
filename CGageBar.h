#pragma once
#include "CObject.h"

class CGageBar :
	public CObject
{
	float* m_fMax;
	float* m_fCur;
	float m_fWidth;

	Vector3* m_vTargetPos;
	Vector3 m_vOffset;
public:
	CGageBar(float *Max, float*Cur, Vector3*TargetPos, Vector3 Offset,
		CTexture* Texture);
	virtual ~CGageBar();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

};

