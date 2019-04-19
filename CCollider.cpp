#include "DXUT.h"
#include "CCollider.h"

#include "CObject.h"

CCollider::CCollider(CObject * pOwner)
	:m_pOwner(pOwner)
{
}

CCollider::~CCollider()
{
}

void CCollider::SetCollider(float left, float top, float right, float bottom)
{
	m_rcRange.left = left;
	m_rcRange.top = top;
	m_rcRange.right = right;
	m_rcRange.bottom = bottom;
}

void CCollider::SetCollider(float width, float height)
{
	m_rcRange.left = -width/2.f;
	m_rcRange.top = -height/2.f;
	m_rcRange.right = width/2.f;
	m_rcRange.bottom = height/2.f;
}

void CCollider::SetCollider(float size)
{
	m_rcRange.left = -size / 2.f;
	m_rcRange.top = -size / 2.f;
	m_rcRange.right = size / 2.f;
	m_rcRange.bottom = size / 2.f;
}

void CCollider::SetCollider(const RECT & collider)
{
	m_rcRange = collider;
}

const RECT & CCollider::GetReal()
{
	Vector3 vPos = m_pOwner->GetInfo()->vPos;

	// TODO: 여기에 반환 구문을 삽입합니다.
	RECT ret = { m_rcRange.left	  + vPos.x,
				 m_rcRange.top	  + vPos.y,
				 m_rcRange.right  + vPos.x,
				 m_rcRange.bottom + vPos.y };

	return ret;
}

bool CCollider::IsInside(Vector3 vPoint)
{
	
	RECT rc = GetReal();

	return { rc.left < vPoint.x && rc.right > vPoint.x &&
	rc.top < vPoint.y && rc.bottom > vPoint.y };
}