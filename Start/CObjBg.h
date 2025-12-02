#pragma once
#include "CObj.h"
class CObjBg: public CObj
{
public:
	CObjBg();
	virtual ~CObjBg();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

};

