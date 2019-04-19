#pragma once
#include "CTexture.h"
class CMultiTexture :
	public CTexture
{
private:
	vector<CTexture*> vecTexts;
public:
	CMultiTexture();
	virtual ~CMultiTexture();

	virtual CTexture* AddImage(const string& path, int count = 0) override;
	virtual CTexture* GetImage(int count = -1) override;

	virtual int Length() override;
};

