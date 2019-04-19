#pragma once

class CCollider;

class CCollisionAdmin
{
private:
	std::list<CCollider*>* m_listCollider;
public:
	CCollisionAdmin();
	~CCollisionAdmin();

	void CollisionCheck();

	void RegisterCollider(CCollider* _tCol);
	void UnRegisterCollider(CCollider* _tCol);

	void ListClear() { m_listCollider->clear(); }
};