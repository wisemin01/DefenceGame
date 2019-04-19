#include "DXUT.h"
#include "CSingleTexture.h"


CSingleTexture::CSingleTexture()
{
}


CSingleTexture::~CSingleTexture()
{
	SAFE_RELEASE(texture);
}

CTexture * CSingleTexture::AddImage(const string & path, int count)
{
	D3DXGetImageInfoFromFileA(path.c_str(), &info);

	D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(), path.c_str(), info.Width, info.Height, info.MipLevels, 0, info.Format, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(10, 10, 10), &info, NULL, &texture);

	return this;
}

CTexture * CSingleTexture::GetImage(int count)
{
	return this;
}

int CSingleTexture::Length()
{
	return 1;
}
