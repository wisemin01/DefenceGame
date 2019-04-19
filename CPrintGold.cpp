#include "DXUT.h"
#include "CPrintGold.h"


CPrintGold::CPrintGold()
	: CMoveText("", V3ZERO, { 0,0,0,0 })
{
	m_tInfo.tColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_tInfo.vPos.y = 10;
}

CPrintGold::~CPrintGold()
{
}

void CPrintGold::Update()
{
	//CMoveText::Update();
	sText = " GOLD:" + to_string((INT)DATA.GetGold()) + " MANA:" + to_string(SKILL.GetMana());
}

void CPrintGold::Render()
{
	IMAGE.PrintText(sText, m_tInfo.vPos.x, m_tInfo.vPos.y, 50, m_tInfo.tColor);
}
