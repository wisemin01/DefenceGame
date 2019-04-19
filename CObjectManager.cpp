#include "DXUT.h"
#include "CObjectManager.h"

#include "CObject.h"
#include "CCollisionAdmin.h"

CObjectManager::CObjectManager()
{
	Init();

	m_pCollision = new CCollisionAdmin();
}


CObjectManager::~CObjectManager()
{
	Destroy();

	SAFE_DELETE(m_pCollision);
}

CObject * CObjectManager::AddObject(OBJKIND iKind, CObject * pObj)
{
	if (pObj) {
		pObj->Init();

		m_listObj[iKind].push_back(pObj);
	}

	return pObj;
}

CObject * CObjectManager::AddUI(UIOBJKIND iKind, CObject * pObj)
{
	if (pObj) {
		pObj->Init();

		m_UiListObj[iKind].push_back(pObj);
	}

	return pObj;
}

std::list<CObject*>& CObjectManager::GetList(OBJKIND iKind)
{
	return m_listObj[iKind];
}

std::list<CObject*>& CObjectManager::GetList(UIOBJKIND iKind)
{
	return m_UiListObj[iKind];
}

void CObjectManager::MoveOtherList(CObject * pObj, UIOBJKIND iKind)
{
	for (int i = 0; i < OBJKIND::END; i++) {
		std::list<CObject*>& ref = m_listObj[i];

		for (auto obj = ref.begin(); obj != ref.end();)
		{
			if ((*obj) == pObj)
			{
				obj = ref.erase(obj);
			}
			else
				obj++;
		}
	}
	for (int i = 0; i < UIOBJKIND::UI_END; i++) {
		std::list<CObject*>& ref = m_UiListObj[i];

		for (auto obj = ref.begin(); obj != ref.end();)
		{
			if ((*obj) == pObj)
			{
				obj = ref.erase(obj);
			}
			else
				obj++;
		}
	}

	AddUI(iKind, pObj);
}

void CObjectManager::MoveOtherList(CObject * pObj, OBJKIND iKind)
{
	for (int i = 0; i < OBJKIND::END; i++) {
		std::list<CObject*>& ref = m_listObj[i];

		for (auto obj = ref.begin(); obj != ref.end();)
		{
			if ((*obj) == pObj)
			{
				obj = ref.erase(obj);
			}
			else
				obj++;
		}
	}
	for (int i = 0; i < UIOBJKIND::UI_END; i++) {
		std::list<CObject*>& ref = m_UiListObj[i];

		for (auto obj = ref.begin(); obj != ref.end();)
		{
			if ((*obj) == pObj)
			{
				obj = ref.erase(obj);
			}
			else
				obj++;
		}
	}

	AddObject(iKind, pObj);
}

void CObjectManager::ClearList(OBJKIND iKind)
{
	for (auto obj : m_listObj[iKind])
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
	m_listObj[iKind].clear();
}

void CObjectManager::ClearUIList(UIOBJKIND iKind)
{
	for (auto obj : m_UiListObj[iKind])
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
	m_UiListObj[iKind].clear();
}

void CObjectManager::RegisterCollider(CCollider * col)
{
	m_pCollision->RegisterCollider(col);
}

void CObjectManager::UnRegisterCollider(CCollider * col)
{
	m_pCollision->UnRegisterCollider(col);
}

void CObjectManager::Init()
{
}

void CObjectManager::Update()
{
	m_RenderingList.clear();

	for (int i = 0; i < OBJKIND::END; i++) {
		std::list<CObject*>& ref = m_listObj[i];

		for (auto obj = ref.begin(); obj != ref.end();)
		{
			if ((*obj)->GetDelete())
			{
				(*obj)->Destroy();
				SAFE_DELETE(*obj);
				obj = ref.erase(obj);
			}
			else
			{
				(*obj)->Update();
				m_RenderingList.push_back(*obj);

				obj++;
			}
		}
	}

	for (int i = 0; i < UIOBJKIND::UI_END; i++)
	{
		std::list<CObject*>& ref = m_UiListObj[i];

		for (auto obj = ref.begin(); obj != ref.end();)
		{
			if ((*obj)->GetDelete())
			{
				(*obj)->Destroy();
				SAFE_DELETE(*obj);
				obj = ref.erase(obj);
			}
			else
			{
				(*obj)->Update();

				obj++;
			}
		}
	}

	m_pCollision->CollisionCheck();

	SetRenderingList();
}

void CObjectManager::Render()
{
	for (auto iter : m_RenderingList)
		iter->Render();
	IMAGE.ReBegin(true);
	for (auto iter : m_UiListObj[UIOBJKIND::SCREEN])
		iter->Render();
	IMAGE.ReBegin(false);
}

void CObjectManager::Destroy()
{
	for (int i = 0; i < OBJKIND::END; i++)
		ClearList((OBJKIND)i);
	for (int i = 0; i < UIOBJKIND::UI_END; i++)
		ClearUIList((UIOBJKIND)i);
}

void CObjectManager::SetRenderingList()
{
	for (auto obj : m_UiListObj[UIOBJKIND::SCROLL])
		if (!obj->GetDelete())
			m_RenderingList.push_back(obj);

	m_RenderingList.sort(CObject::CompareY);
	m_RenderingList.sort(CObject::CompareDepth);
}
