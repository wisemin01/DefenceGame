#pragma once
#include "CSingleton.h"

enum OBJKIND
{
	NORMAL,
	DROP_POINT,
	TOWER,
	ENEMY,
	EFFECT,
	SPAWN,
	BULLET,
	CORE,
	END
};

enum UIOBJKIND
{
	SCREEN,
	SCROLL,
	UI_END
};

class CObject;
class CCollisionAdmin;
class CCollider;
class CObjectManager :
	public CSingleton<CObjectManager>
{
private:
	std::list<CObject*> m_listObj  [OBJKIND::END];
	std::list<CObject*> m_UiListObj[UIOBJKIND::UI_END];

	std::list<CObject*> m_RenderingList;

private:
	CCollisionAdmin * m_pCollision = nullptr;
public:
	CObjectManager();
	virtual ~CObjectManager();

	CObject* AddObject(OBJKIND iKind, CObject* pObj);
	CObject* AddUI(UIOBJKIND iKind, CObject* pObj);

	std::list<CObject*>& GetList(OBJKIND iKind);
	std::list<CObject*>& GetList(UIOBJKIND iKind);

	void MoveOtherList(CObject* pObj, UIOBJKIND iKind);
	void MoveOtherList(CObject* pObj, OBJKIND iKind);

	void ClearList(OBJKIND iKind);
	void ClearUIList(UIOBJKIND iKind);

	void RegisterCollider(CCollider* col);
	void UnRegisterCollider(CCollider* col);

	void Init();
	void Update();
	void Render();
	void Destroy();

	size_t GetListSize(OBJKIND iKind) { return m_listObj[iKind].size(); }
	size_t GetListSize(UIOBJKIND iKind) { return m_UiListObj[iKind].size(); }

private:
	void SetRenderingList();
};

#define OBJECT (*CObjectManager::GetInstance())

#define REGISTERCOLLIDER	OBJECT.RegisterCollider(&(this->m_tCollider))
#define UNREGISTERCOLLIDER	OBJECT.UnRegisterCollider(&(this->m_tCollider))