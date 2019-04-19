#pragma once
#include "CBullet.h"
class CCurveBullet :
	public CBullet
{
protected:
	Vector3 vStartPos;
	Vector3 vDestPos;
	Vector3 vSpeed;

	Vector3 *vTargetPos = nullptr;

	float g				= 0.f;
	float fDestTime		= 0.f;
	float fHeight		= 0.f;
	float fDestHeight	= 0.f;
	float fAccrueTime	= 0.f;
	float fMaxHeight	= 0.f;
	float fMaxAchieveTime = 0.f;

	bool  bAttackStart = false;
public:
	CCurveBullet(Vector3 vStart, Vector3* vTarget, float MaxTime, float Size, float Damage);
	virtual ~CCurveBullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* _tCol) override;

	void PreCalculate();
	void SetClamBullet(Vector3 _vStartPos, Vector3 _vDestPos, float MaxAchiveTime);
};

