#include "DXUT.h"
#include "CSlow.h"

#include "CTexture.h"
#include "CEnemy.h"

CSlow::CSlow(Vector3 vPos, float size)
{
	m_tInfo.vPos = vPos;
	m_tCollider.SetCollider(size);
	m_tInfo.iDepth = 10;
}

CSlow::~CSlow()
{
}

void CSlow::Init()
{
	SetFrame(0, 10, 100);
	SetTexture("SLOW");
	REGISTERCOLLIDER;
}

void CSlow::Update()
{
	m_tFrame.Frame();
	if (m_tFrame.CurFrame == m_tFrame.EndFrame)
	{
		SetDelete(true);
	}
}

void CSlow::Render()
{
	IMAGE.Render(m_pTexture->GetImage(m_tFrame.CurFrame), m_tInfo.vPos);
}

void CSlow::Destroy()
{
	UNREGISTERCOLLIDER;
}

void CSlow::OnCollision(CCollider * col)
{
	if (col->GetOwner()->GetInfo()->sTag == "ENEMY")
	{
		reinterpret_cast<CEnemy*>(col->GetOwner())->SetSlow(4000);
	}
}
