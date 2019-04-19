#pragma once
class CCollider
{
private:
	RECT m_rcRange;

	CObject* m_pOwner = nullptr;
public:
	CCollider(CObject* pOwner);
	virtual ~CCollider();

	void SetCollider(float left, float top, float right, float bottom);
	void SetCollider(float width, float height);
	void SetCollider(float size);
	void SetCollider(const RECT& collider);

	const RECT& GetReal();

	bool IsInside(Vector3 vPoint);

	CObject* GetOwner() { return m_pOwner; }
};

