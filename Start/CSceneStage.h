#pragma once
#include "CScene.h"
class CSceneStage: public CScene
{
public:
	CSceneStage();
	virtual ~CSceneStage();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

