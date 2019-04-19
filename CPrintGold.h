#pragma once
#include "CMoveText.h"
class CPrintGold :
	public CMoveText
{
public:
	CPrintGold();
	~CPrintGold();

	virtual void Update() override;
	virtual void Render() override;
};

