#pragma once

#include "Define.h"

class CMainGame
{
public:
	CMainGame();
	virtual ~CMainGame();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	TCHAR m_szFPS[128];
	int m_iFPS;
	DWORD m_dwFPSTime;

	HDC m_hDC;
};

