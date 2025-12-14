#pragma once
#include "CScene.h"
class CSceneMonster :
    public CScene
{
public:
	CSceneMonster();
	virtual ~CSceneMonster();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	DWORD m_dwSurveyDronIntervalTime;

	bool m_bRoom1Enter;

	bool m_bRoom2Enter;

	bool m_bRoom3Enter;
};

