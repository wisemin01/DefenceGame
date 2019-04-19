#pragma once
class CMaingame
{
public:
	CMaingame();
	~CMaingame();

	void Init();
	void Update();
	void Render();
	void Destroy();

	void ResetDevice();
	void LostDevice();
};

