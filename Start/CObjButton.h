#pragma once
#include "CObj.h"
class CObjButton: public CObj
{
public:
	CObjButton();
	virtual ~CObjButton();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int     m_iDrawID;
};

