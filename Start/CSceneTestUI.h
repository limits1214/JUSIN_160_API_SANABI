#pragma once
#include "CScene.h"
class CSceneTestUI: public CScene
{
public:
	CSceneTestUI();
	virtual ~CSceneTestUI();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

