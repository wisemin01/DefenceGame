#pragma once
#include "CObject.h"
class CBackground :
	public CObject
{
public:
	CBackground();
	virtual ~CBackground();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

