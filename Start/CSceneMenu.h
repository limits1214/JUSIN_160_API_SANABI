#pragma once
#include "CScene.h"
class CSceneMenu: public CScene
{
public:
	CSceneMenu();
	virtual ~CSceneMenu();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

