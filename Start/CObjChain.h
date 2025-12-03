#pragma once
#include "CObjLine.h"

class CObjChain: public CObjLine
{
public:
	CObjChain();
	virtual ~CObjChain();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

