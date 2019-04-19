#include "DXUT.h"
#include "CMultiTexture.h"
#include "CSingleTexture.h"

CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	for (auto iter : vecTexts)
	{
		SAFE_DELETE(iter);
	}
}

CTexture * CMultiTexture::AddImage(const string& path, int count)
{
	char sz[128] = "";

	for (int i = 1; i <= count; i++)
	{
		sprintf(sz, path.c_str(), i);

		CTexture* pTex = new CSingleTexture;
		pTex->AddImage(sz);

		vecTexts.push_back(pTex);
	}

	return this;
}

CTexture * CMultiTexture::GetImage(int count)
{
	if (count == -1)
		return this;
	else return vecTexts[count];
}

int CMultiTexture::Length()
{
	return vecTexts.size();
}
