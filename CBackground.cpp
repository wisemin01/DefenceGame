#include "DXUT.h"
#include "CBackground.h"

#include "CTexture.h"

CBackground::CBackground()
{
}


CBackground::~CBackground()
{
}

void CBackground::Init()
{
}

void CBackground::Update()
{
}

void CBackground::Render()
{
	for (int i = 0; i < m_pTexture->Length(); i++)
	{
		IMAGE.Render(m_pTexture->GetImage(i), m_tInfo.vPos);
	}
}

void CBackground::Destroy()
{
}
