#include "DXUT.h"
#include "CEffectSpawn.h"
#include "CMoveObject.h"


CEffectSpawn::CEffectSpawn(float width, float height, int iTypeLimit)
	: m_fScreenWidth(width),m_fScreenHeight(height), m_iTypeLimit(iTypeLimit)
{

}

CEffectSpawn::~CEffectSpawn()
{

}

void CEffectSpawn::Init()
{

}

void CEffectSpawn::Update()
{
	if (m_fFrameSkip <= GetNowTime())
	{
		Bubble();

		m_fFrameSkip = GetNowTime() + 1000;
	}

	if (m_iTypeLimit > 0 && m_fFrameSkip2 <= GetNowTime())
	{
		Fish();

		m_fFrameSkip2 = GetNowTime() + 10000;
	}

	if (m_iTypeLimit > 1 && m_fFrameSkip3 <= GetNowTime())
	{
		BigFish();

		m_fFrameSkip3 = GetNowTime() + 25000;
	}
}

void CEffectSpawn::Render()
{

}

void CEffectSpawn::Destroy()
{

}

void CEffectSpawn::Bubble()
{
	auto moveObj = new CMoveObject(
		Vector3(GetRand(100, m_fScreenWidth - 100), m_fScreenHeight + 50, 0),
		Vector3(GetRand(-30, 30), -100, 0),
		10000
	);

	OBJECT.AddObject(OBJKIND::EFFECT, moveObj);
	moveObj->GetInfo()->iDepth = 10;

	moveObj->SetTexture("BUBBLE");
	float f = GetRand(3, 7) * 0.1;
	moveObj->GetInfo()->vScale = Vector3(f, f, f);
}

void CEffectSpawn::Fish()
{
	auto moveObj = new CMoveObject(
		Vector3(m_fScreenWidth + 300, GetRand(m_fScreenHeight / 2.f, m_fScreenHeight), 0)
		, Vector3(-70, -10, 0),
		30000
	);

	OBJECT.AddObject(OBJKIND::EFFECT, moveObj);
	moveObj->GetInfo()->iDepth = 10;

	moveObj->SetTexture("SMALL_FISH");
	moveObj->GetInfo()->tColor = D3DCOLOR_ARGB(150, 255, 255, 255);
}

void CEffectSpawn::BigFish()
{
	auto moveObj = new CMoveObject(
		Vector3(m_fScreenWidth + 300, GetRand(m_fScreenHeight / 2.f, m_fScreenHeight), 0),
		Vector3(-80, -20, 0),
		40000
	);

	OBJECT.AddObject(OBJKIND::EFFECT, moveObj);
	moveObj->GetInfo()->iDepth = 10;

	moveObj->SetTexture("BIG_FISH");
	float f = GetRand(7, 9) * 0.1;
	moveObj->GetInfo()->vScale = Vector3(f, f, 1);
	moveObj->GetInfo()->tColor = D3DCOLOR_ARGB(90, 255, 255, 255);
}
