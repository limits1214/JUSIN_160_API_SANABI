#pragma once
#include "CScene.h"
class CSceneBoss: public CScene
{
public:
	CSceneBoss();
	virtual ~CSceneBoss();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

