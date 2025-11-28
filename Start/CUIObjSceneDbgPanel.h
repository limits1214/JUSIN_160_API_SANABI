#pragma once

#include "CUIObjPanel.h"

class CUIObjSceneDbgPanel: public CUIObjPanel
{
public:
	CUIObjSceneDbgPanel();
	virtual ~CUIObjSceneDbgPanel();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

