#pragma once
class CTexture abstract
{
public:
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;
public:
	CTexture();
	virtual ~CTexture();

	virtual CTexture* AddImage(const string& path, int count = 0) PURE;
	virtual CTexture* GetImage(int count = -1) PURE;

	virtual int Length() PURE;
};

