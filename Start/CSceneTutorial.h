#pragma once

#include "CScene.h"

class CSceneTutorial: public CScene
{
public:
	CSceneTutorial();
	virtual ~CSceneTutorial();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

