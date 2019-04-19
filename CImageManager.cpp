#include "DXUT.h"
#include "CImageManager.h"

#include "CMultiTexture.h"
#include "CSingleTexture.h"

CImageManager::CImageManager()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &m_pSprite);
}


CImageManager::~CImageManager()
{
	SAFE_RELEASE(m_pSprite);

	for (auto iter : m_mapTexture)
	{
		SAFE_DELETE(iter.second);
	}
	m_mapTexture.clear();
}

CTexture * CImageManager::AddImage(const string & key, const string & path, int count)
{
	auto find = m_mapTexture.find(key);

	if (find == m_mapTexture.end()) {

		CTexture* ret;

		if (count == 0)
		{
			ret = new CSingleTexture();
		}
		else
		{
			ret = new CMultiTexture();
		}

		ret->AddImage(path, count);

		m_mapTexture.insert(make_pair(key, ret));

		return ret;
	}
	return nullptr;
}

CTexture * CImageManager::GetImage(const string & key, int count)
{
	auto find = m_mapTexture.find(key);

	if (find != m_mapTexture.end())
	{
		return find->second->GetImage(count);
	}
	else
	{
		return nullptr;
	}
}

void CImageManager::Begin(bool _bIsInterface)
{
	DWORD flag = D3DXSPRITE_ALPHABLEND;

	if (!_bIsInterface)
		flag |= D3DXSPRITE_OBJECTSPACE;

	m_pSprite->Begin(flag);
}

void CImageManager::End()
{
	m_pSprite->End();
}

void CImageManager::LostDevice()
{
	m_pSprite->OnLostDevice();
}

void CImageManager::ResetDevice()
{
	m_pSprite->OnResetDevice();
}

void CImageManager::PrintText(const string& str, float x, float y, float size, D3DCOLOR color)
{
	LPD3DXFONT pFont;
	D3DXMATRIX mat;

	D3DXCreateFontA(DXUTGetD3D9Device(), size, 0, 10, 1,
		FALSE, HANGUL_CHARSET, 0, 0, 0, "Fixedsys", &pFont);

	D3DXMatrixTranslation(&mat, x, y, 0);

	m_pSprite->SetTransform(&mat);
	pFont->DrawTextA(m_pSprite, str.c_str(), str.size(), NULL, DT_NOCLIP, color);
	SAFE_RELEASE(pFont);
}

void CImageManager::PrintCenterText(const string & str, float x, float y, float size, D3DCOLOR color)
{
	LPD3DXFONT pFont;
	D3DXMATRIX mat;

	D3DXCreateFontA(DXUTGetD3D9Device(), size, 0, 0, 1,
		FALSE, HANGUL_CHARSET, 0, 0, 0, "Fixedsys", &pFont);

	D3DXMatrixTranslation(&mat, x - size * (str.size() * 0.25), y - size / 2.f, 0);

	m_pSprite->SetTransform(&mat);
	pFont->DrawTextA(m_pSprite, str.c_str(), str.size(), NULL, DT_CENTER | DT_NOCLIP, color);
	SAFE_RELEASE(pFont);
}

void CImageManager::DrawLine(Vector2* vecList, int count, float width, bool bIsAntialias, D3DCOLOR color)
{
	ID3DXLine* ILine;

	D3DXCreateLine(DXUTGetD3D9Device(), &ILine);

	ILine->SetWidth(width);
	ILine->SetAntialias(bIsAntialias);
	ILine->Begin();

	ILine->Draw(vecList, count, color);
	ILine->End();
	SAFE_RELEASE(ILine);
}

void CImageManager::Render(CTexture * pTexture, const Vector3 & vPos, float fRot, DWORD tColor)
{
	if (pTexture) {
		D3DXMATRIX mat;
		Vector3 vCenter(pTexture->info.Width / 2.f, pTexture->info.Height / 2.f, 0);

		D3DXMatrixAffineTransformation2D(&mat, 1.0f, NULL, D3DXToRadian(fRot), &Vector2(vPos.x, vPos.y));

		m_pSprite->SetTransform(&mat);
		m_pSprite->Draw(pTexture->texture, NULL, &vCenter, NULL, tColor);
	}
}

void CImageManager::ScaleRender(CTexture * pTexture, const Vector3 & vPos, const Vector3 & vScale, float fRot, DWORD tColor)
{
	if (pTexture) {
		D3DXMATRIX mat;
		D3DXMATRIX matS, matT, matR;

		D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
		D3DXMatrixTranslation(&matT, vPos.x, vPos.y, 0);
		D3DXMatrixRotationZ(&matR, D3DXToRadian(fRot));

		mat = matS * matT * matR;

		m_pSprite->SetTransform(&mat);
		m_pSprite->Draw(pTexture->texture, NULL,
			&Vector3(pTexture->info.Width / 2.f, pTexture->info.Height / 2.f, 0), NULL, tColor);
	}
}

void CImageManager::CropRender(CTexture * pTexture, const Vector3 & vPos, const RECT & rcRange)
{
	m_pSprite->Draw(pTexture->texture, &rcRange, &Vector3(
		pTexture->info.Width / 2, pTexture->info.Height / 2, 0), nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CFrame::SetFrame(int start, int end, unsigned long delay)
{
	CurFrame = StartFrame = start;
	EndFrame = end;
	FrameDelay = delay;
	FrameSkip = FrameDelay + GetNowTime();
}

bool CFrame::Frame()
{
	if (FrameSkip <= GetNowTime())
	{
		if (CurFrame >= EndFrame)
		{
			CurFrame = StartFrame;
		}
		else CurFrame++;

		FrameSkip = FrameDelay + GetNowTime();
		return true;
	}
	return false;
}
