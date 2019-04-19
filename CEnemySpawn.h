#pragma once
#include "CObject.h"
class CEnemySpawn :
	public CObject
{
private:
	std::vector <pair<float,CObject*>> m_vecEnemys;
	int m_iNowEnemy;
	float m_fFrameSkip;

	bool m_bOnSpawning = true;

	float m_fPageTime = 0;

public:
	CEnemySpawn();
	virtual ~CEnemySpawn();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void InsertEnemy(float delay, CObject* enemy);

	void CreateWave(int stageNum, const string & waveText,
		int count, float delayToNextWave, int hp, int deathCost,
		int speed, int attackDamage, float delayToNextUnit,
		int FrameInterval, CTexture * pTexture);
};

