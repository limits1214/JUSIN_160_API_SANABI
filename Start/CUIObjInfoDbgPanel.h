#pragma once
#include "CUIObjPanel.h"
class CUIObjInfoDbgPanel: public CUIObjPanel
{
public:
	CUIObjInfoDbgPanel();
	virtual ~CUIObjInfoDbgPanel();

public:
	void Set_ObjSeq(unsigned long long seq) { m_lObjSeq = seq; }

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	unsigned long long m_lObjSeq;
};

