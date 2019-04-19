#include "DXUT.h"
#include "CCollisionAdmin.h"

#include "CCollider.h"
#include "CObject.h"

CCollisionAdmin::CCollisionAdmin()
{
	m_listCollider = new list<CCollider*>;
}

CCollisionAdmin::~CCollisionAdmin()
{
	ListClear();
	SAFE_DELETE(m_listCollider);
}

void CCollisionAdmin::CollisionCheck()
{
	for (auto col1 : *m_listCollider)
	{
		for (auto col2 : *m_listCollider)
		{
			if (col1 == col2)
				continue;

			RECT range;

			RECT rc1 = col1->GetReal();
			RECT rc2 = col2->GetReal();

			if (IntersectRect(&range, &rc1, &rc2))
			{
				col1->GetOwner()->OnCollision(col2);
			}
		}
	}
}

void CCollisionAdmin::RegisterCollider(CCollider * _tCol)
{
	m_listCollider->push_back(_tCol);
}

void CCollisionAdmin::UnRegisterCollider(CCollider * _tCol)
{
	m_listCollider->remove(_tCol);
}
