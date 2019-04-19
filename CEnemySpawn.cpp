#include "DXUT.h"
#include "CEnemySpawn.h"

#include "CMoveText.h"
#include "CBlackout.h"

#include "CEnemy.h"

CEnemySpawn::CEnemySpawn()
{
}


CEnemySpawn::~CEnemySpawn()
{
}

void CEnemySpawn::Init()
{
	m_iNowEnemy = 0;
	m_fFrameSkip = 0;
	m_fPageTime = 0;
	m_bOnSpawning = true;
}

void CEnemySpawn::Update()
{
	if (m_bOnSpawning) {
		if (m_fFrameSkip <= GetNowTime()) {
			if (m_vecEnemys[m_iNowEnemy].second)
				OBJECT.AddObject(OBJKIND::ENEMY, m_vecEnemys[m_iNowEnemy].second);

			m_fFrameSkip = GetNowTime() + m_vecEnemys[m_iNowEnemy].first;

			m_iNowEnemy++;
			if (m_iNowEnemy >= m_vecEnemys.size())
			{
				m_bOnSpawning = false;
			}
		}
	}
	else if(m_fPageTime == 0 && OBJECT.GetListSize(OBJKIND::ENEMY) == 0)
	{
		auto text = new CMoveText("- STAGE CLEAR! -", Vector3(WINSIZEX / 2, 200, 0), COLORVALUE_DEFAULT, Vector3(0, -4, 0), 5000, true, 100);
		text->SetAlphaDownSpeed(0.5);
		OBJECT.AddUI(UIOBJKIND::SCREEN, text);
		m_fPageTime = GetNowTime() + 3000;
	}
	
	if (m_fPageTime != 0 && m_fPageTime <= GetNowTime())
	{
		OBJECT.AddUI(UIOBJKIND::SCREEN, new CBlackout([&]() {
			string scene = SCENE.GetNowSceneName();
			if (scene == "S_STAGE1")
				SCENE.ChangeScene("S_STAGE2");
			else if (scene == "S_STAGE2")
				SCENE.ChangeScene("S_STAGE3");
			else if (scene == "S_STAGE3")
				SCENE.ChangeScene("S_CLEAR");
		}, 0));
		SetDelete(true);
	}
}

void CEnemySpawn::Render()
{
}

void CEnemySpawn::Destroy()
{
	for (int i = m_iNowEnemy; i < m_vecEnemys.size(); i++)
	{
		m_vecEnemys[i].second->Destroy();
		SAFE_DELETE(m_vecEnemys[i].second);
	}
	m_vecEnemys.clear();
}

void CEnemySpawn::InsertEnemy(float delay, CObject * enemy)
{
	m_vecEnemys.push_back(make_pair(delay, enemy));
}

void CEnemySpawn::CreateWave(int stageNum, const string & waveText,
	int count, float delayToNextWave, int hp, int deathCost,
	int speed, int attackDamage, float delayToNextUnit,
	int FrameInterval, CTexture * pTexture)
{
	auto moveText = new CMoveText(waveText,
		Vector3(WINSIZEX / 2, 200, 0), { 255,255,255,255 }, Vector3(0, -5, 0), 5000, true, 100);
	moveText->SetAlphaDownSpeed(0.5);

	auto firstEnemy = new CEnemy(stageNum, hp, speed, deathCost, attackDamage, moveText);
	firstEnemy->SetTexture(pTexture);
	firstEnemy->SetInterval(FrameInterval);

	InsertEnemy(delayToNextUnit, firstEnemy);
	for (int i = 0; i < count - 2; i++)
		InsertEnemy(delayToNextUnit, new CEnemy(stageNum, hp, speed, deathCost, attackDamage, pTexture, FrameInterval));

	InsertEnemy(delayToNextWave, new CEnemy(stageNum, hp, speed, deathCost, attackDamage, pTexture, FrameInterval));

}