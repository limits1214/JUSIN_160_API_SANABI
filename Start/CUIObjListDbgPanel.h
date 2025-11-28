#pragma once

#include "CUIObjPanel.h"

class CUIObjListDbgPanel: public CUIObjPanel
{
public:
	CUIObjListDbgPanel();
	virtual ~CUIObjListDbgPanel();

public:
	void Set_ObjID(OBJID eID)
	{
		m_eObjID = eID;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	OBJID m_eObjID;
};

