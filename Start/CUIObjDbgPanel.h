#pragma once
#include "CUIObjPanel.h"

class CUIObjDbgPanel: public CUIObjPanel
{
public:
	CUIObjDbgPanel();
	virtual ~CUIObjDbgPanel();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

