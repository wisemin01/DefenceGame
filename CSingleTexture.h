#pragma once
#include "CTexture.h"
class CSingleTexture :
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

	virtual CTexture* AddImage(const string& path, int count = 0) override;
	virtual CTexture* GetImage(int count = -1) override;

	virtual int Length() override;
};

