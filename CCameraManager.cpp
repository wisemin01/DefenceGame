#include "DXUT.h"
#include "CCameraManager.h"


CCameraManager::CCameraManager()
{
	Init();
}


CCameraManager::~CCameraManager()
{
}

void CCameraManager::Init()
{
	m_vCameraPos = V3CENTER;
	m_vViewSize = Vector3(WINSIZEX, WINSIZEY, 0);
	m_vScale = Vector3(1, 1, 1);

	m_fAngle = 0.0f;

	D3DXMatrixOrthoLH(&m_matProj, m_vViewSize.x, -m_vViewSize.y, 0, 1);
}

void CCameraManager::Update()
{
	this->m_matView = D3DXMATRIX(
		m_vScale.x * cosf(m_fAngle), m_vScale.x * sin(m_fAngle), 0, 0,
		-m_vScale.y * sin(m_fAngle), m_vScale.y * cos(m_fAngle), 0, 0,
		0, 0, m_vScale.z, 0,
		-m_vCameraPos.x * m_vScale.y * cos(m_fAngle) + m_vCameraPos.y * m_vScale.y * sin(m_fAngle),
		-m_vCameraPos.x * m_vScale.x * sin(m_fAngle) - m_vCameraPos.y * m_vScale.y * cos(m_fAngle), 0, 1);
}

void CCameraManager::SetTranform()
{
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &m_matView);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &m_matProj);
}
