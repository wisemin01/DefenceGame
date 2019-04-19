#pragma once
#include "CObject.h"
class CMoveObject :
	public CObject
{
private:
	Vector3 m_vVel;

	float m_fEndTime;
public:
	CMoveObject(Vector3 vStart, Vector3 vVel, float fEndTime);
	CMoveObject() {}
	virtual ~CMoveObject();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetVel(Vector3 vel) { m_vVel = vel; }
};

