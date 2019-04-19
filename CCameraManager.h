#pragma once
#include "CSingleton.h"

class CObject;
class CCameraManager :
	public CSingleton<CCameraManager>
{
private:
	D3DXMATRIX m_matProj, m_matView;

	Vector3 m_vCameraPos, m_vViewSize, m_vScale;

	CObject* m_pTarget = nullptr;

	float m_fAngle = 0.0;

public:
	CCameraManager();
	virtual ~CCameraManager();

	void SetFollow(CObject* pTarget) { m_pTarget = pTarget; }

	void SetPosition	(const Vector3& vSet)	{ m_vCameraPos = vSet; }
	void MovePosition	(const Vector3& vPlus)	{ m_vCameraPos += vPlus; }

	Vector3 GetPosition() { return m_vCameraPos; }

	void Init();
	void Update();
	void SetTranform();
};

#define CAMERA (*CCameraManager::GetInstance())