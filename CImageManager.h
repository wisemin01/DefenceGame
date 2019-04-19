#pragma once
#include "CSingleton.h"

class CTexture;

class CFrame
{
public:
	int CurFrame = 0;
	int StartFrame = 0;
	int EndFrame = 0;

	unsigned long FrameSkip = 0;
	unsigned long FrameDelay = 0;

	void SetFrame(int start, int end, unsigned long delay);

	bool Frame();
};

class CImageManager :
	public CSingleton<CImageManager>
{
private:
	map<string, CTexture*> m_mapTexture;
	LPD3DXSPRITE m_pSprite = nullptr;

	list<pair<string, D3DCOLORVALUE>> m_systemLogs;

public:
	CImageManager();
	virtual ~CImageManager();

	CTexture* AddImage(const string& key, const string& path, int count = 0);
	CTexture* GetImage(const string& key, int count = -1);

	void Begin(bool _bIsInterface);
	void End();
	void ReBegin(bool _bIsInterface) { End(); Begin(_bIsInterface); }
	void LostDevice();
	void ResetDevice();

	void PrintText(const string& str, float x, float y, float size, D3DCOLOR color);
	void PrintCenterText(const string& str, float x, float y, float size, D3DCOLOR color);

	void DrawLine(Vector2* vecList,int count, float width,bool bIsAntialias, D3DCOLOR color);

public:

	void Render(CTexture* pTexture, const Vector3& vPos, float fRot = 0.0f, DWORD tColor = D3DCOLOR_XRGB(255, 255, 255));
	void ScaleRender(CTexture* pTexture, const Vector3& vPos, const Vector3& vScale, float fRot = 0.0f, DWORD tColor = D3DCOLOR_XRGB(255, 255, 255));
	void CropRender(CTexture* pTexture, const Vector3& vPos, const RECT& rcRange);

};

#define IMAGE (*CImageManager::GetInstance())