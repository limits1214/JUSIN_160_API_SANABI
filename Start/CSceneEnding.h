#pragma once
#include "CScene.h"
class CSceneEnding :
    public CScene
{
public:
	CSceneEnding();
	virtual ~CSceneEnding();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

