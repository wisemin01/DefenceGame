#pragma once
#include "CObject.h"

class CTowerInfo
{
public:
	float AttackSpeed;
	float AttackDamage;
	float AttackRange;
	float Cost;
};

enum TOWER_LEVEL
{
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL_END
};

enum TOWER_KIND
{
	CLAM,
	CORAL,
	SEA_ANEMONE,
	TOWERKIND_END
};

class CTower :
	public CObject
{
protected:
	CTowerInfo m_tTowerInfo;

	CObject* m_pTarget;

	int m_eKind;
	int m_eLevel;

	float m_fFrameSkip;

	Vector3 vRenderingOffset;
public:
	CTower(Vector3 vPos, int iKind);
	virtual ~CTower();

public:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(CCollider* _tCol) override;

	bool IsCanUpgrade();
	virtual void Upgrade();
	void Sell();

public:
	static CTowerInfo g_tTowerInfo[TOWERKIND_END][LEVEL_END];

	inline static void SetTowerInfo()
	{
		// SPEED DAMAGE RANGE COST
		g_tTowerInfo[CLAM][LEVEL1] = { 800,40,350,60 };
		g_tTowerInfo[CLAM][LEVEL2] = { 750,50,400,65 };
		g_tTowerInfo[CLAM][LEVEL3] = { 700,70,450,70 };

		g_tTowerInfo[CORAL][LEVEL1] = { 400,75,433,75 };
		g_tTowerInfo[CORAL][LEVEL2] = { 350,110,466,100 };
		g_tTowerInfo[CORAL][LEVEL3] = { 300,125,500,125 };

		g_tTowerInfo[SEA_ANEMONE][LEVEL1] = { 1700,400,700,125 };
		g_tTowerInfo[SEA_ANEMONE][LEVEL2] = { 1600,550,750,150 };
		g_tTowerInfo[SEA_ANEMONE][LEVEL3] = { 1500,750,800,175 };
	}

	inline static CTowerInfo GetStaticInfo(int iKind, int iLevel)
	{
		return g_tTowerInfo[iKind][iLevel];
	}

	static bool IsCanDrop(float fNowGold, int iKind);
};

