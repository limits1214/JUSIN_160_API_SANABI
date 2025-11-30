#pragma once
#include "CObj.h"
class CObjRect: public CObj
{
public:
	CObjRect();
	virtual ~CObjRect();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

