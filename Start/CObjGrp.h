#pragma once
#include "CObj.h"
class CObjGrp:public CObj
{
public:
	CObjGrp();
	virtual ~CObjGrp();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

