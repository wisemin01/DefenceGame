#pragma once
#include "CObject.h"

enum ENEMY_STATE
{
	MOVE_SIDE,
	MOVE_FRONT,
	MOVE_BACK,
	ATTACK,
	DEATH
};

class CGageBar;
class CEnemy :
	public CObject
{
private:
	CObject * m_pSpawnObj = nullptr;
	CGageBar* m_myHpBar = nullptr;
private:
	float m_fMaxHp;
	float m_fCurHp;

	float m_fSpeed;
	float m_fDeathCost;

	float m_fAttackDamage;

	int m_iFrameInterval;

	bool m_bIsSlowMode = false;
	float m_fSlowTime;
	float m_fSlowOffset;

	Vector3 m_vOffset;
	Vector3 m_vDir;

	std::vector<Vector3> m_vMyLoad;

	int m_iLastLoadNum;
	int m_iCurLoadNum;

public:
	CEnemy(int stageType, float enemyHp, float enemySpeed, float deathCost, float attackDamage,
		CObject* pSpawn = nullptr);
	CEnemy(int stageType, float enemyHp, float enemySpeed, float deathCost, float attackDamage,
		CTexture* pTexture, int FrameInterval);
	virtual ~CEnemy();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* col) override;

	void SetSlow(float fSlowTime, float fSlowOffset = 0.3f);

	// HP 바꿀때 꼭 사용
	// 피격 데미지 표시기능 & HP음수 방지
	void TakeDamage(float damage);

	void SetInterval(int iInterval) { m_iFrameInterval = iInterval; }
private:

	void MoveUpdate();
	void AttackUpdate();
	void DeathUpdate();

	void SettingOffset(CTexture* pTexture);

public:
	static std::vector<Vector3> g_vEnemyLoad[3][2];

	static void SetEnemyLoad(const std::vector<Vector3>& vecLoad, int stageType, int loadType = 0);

	void SetFrameAsState();
};

