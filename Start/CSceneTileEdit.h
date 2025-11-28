#pragma once

#include "CScene.h"

class CSceneTileEdit: public CScene
{
public:
	CSceneTileEdit();
	virtual ~CSceneTileEdit();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

