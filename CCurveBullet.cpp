#include "DXUT.h"
#include "CCurveBullet.h"
#include "CEnemy.h"
#include "CTexture.h"
#include "CExplode.h"

CCurveBullet::CCurveBullet(Vector3 vStart, Vector3* vTarget, float MaxTime, float Size, float Damage)
	: CBullet(vStart, V3ZERO, Size, 0, Damage)
{
	SetClamBullet(vStart, *vTarget, MaxTime);
	m_tInfo.iDepth = 1;
	vStartPos = vStart;
}

CCurveBullet::~CCurveBullet()
{
}

void CCurveBullet::Init()
{
	SetTexture("BULLET");
	//SetFrame(0, 0, 0);
}

void CCurveBullet::Update()
{
	fAccrueTime += DXUTGetElapsedTime();

	if (fAccrueTime > fDestTime)
	{
		if (bAttackStart)
		{
			OBJECT.AddObject(OBJKIND::EFFECT, new CExplode(m_tInfo.vPos, m_fDamage));
			SetDelete(true);
			return;
		}
		else
		{
			// ADD EFFECT
		}
		bAttackStart = true;
	}

	m_tInfo.vPos.x = vStartPos.x + vSpeed.x * fAccrueTime;
	m_tInfo.vPos.y = (vStartPos.y - vSpeed.y * fAccrueTime + 0.5f * g * fAccrueTime * fAccrueTime);
}

void CCurveBullet::Render()
{
	IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos);
}

void CCurveBullet::Destroy()
{
}

void CCurveBullet::PreCalculate()
{
	fDestHeight = vStartPos.y - vDestPos.y;
	fHeight = (fMaxHeight - vDestPos.y);

	g = 2 * fHeight / (fMaxAchieveTime * fMaxAchieveTime);

	vSpeed.y = sqrt(2 * g * fHeight);

	float a = g;
	float b = -2 * vSpeed.y;
	float c = 2 * fDestHeight;

	fDestTime = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	vSpeed.x = (vDestPos.x - vStartPos.x) / fDestTime;
}


void CCurveBullet::SetClamBullet(Vector3 _vStartPos, Vector3 _vDestPos, float MaxAchiveTime)
{
	m_tInfo.vPos = vStartPos;

	vStartPos = _vStartPos;
	vDestPos = _vDestPos;

	fMaxAchieveTime = MaxAchiveTime;

	if (vStartPos.y < vDestPos.y)
		fMaxHeight = vDestPos.y + 100;
	else
		fMaxHeight = vStartPos.y + 100;

	PreCalculate();
}

void CCurveBullet::OnCollision(CCollider * _tCol)
{
	if (_tCol->GetOwner()->GetInfo()->sTag == "ENEMY")
	{
		if (_tCol->GetOwner()->GetDelete())
			return;

		if (bAttackStart)
		{
			CEnemy * target = (CEnemy*)_tCol->GetOwner();
			target->TakeDamage(m_fDamage);
		}
	}
}