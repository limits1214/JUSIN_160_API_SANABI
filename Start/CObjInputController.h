#pragma once
#include "CObj.h"
class CObjInputController: public CObj
{
public:
	CObjInputController();
	virtual ~CObjInputController();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Key_Input();
};

