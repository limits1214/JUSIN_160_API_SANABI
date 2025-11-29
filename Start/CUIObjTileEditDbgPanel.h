#pragma once


#include "CUIObjPanel.h"

class CUIObjTileEditDbgPanel: public CUIObjPanel
{
public:
	CUIObjTileEditDbgPanel();
	virtual ~CUIObjTileEditDbgPanel();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	TILE_EDIT_MODE m_eTEM;
};

