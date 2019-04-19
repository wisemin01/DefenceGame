#pragma once
#include "CObject.h"
class CEffectSpawn :
	public CObject
{
private:
	float m_fFrameSkip = 0;
	float m_fFrameSkip2 = 0;
	float m_fFrameSkip3 = 0;

	int m_iTypeLimit = 0;

	float m_fScreenWidth;
	float m_fScreenHeight;
public:
	CEffectSpawn(float width, float height, int m_iTypeLimit);
	virtual ~CEffectSpawn();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Bubble();
	void Fish();
	void BigFish();
};

