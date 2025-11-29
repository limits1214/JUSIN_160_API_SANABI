#pragma once
#include "CObjLine.h"
class CObjNoClimableLine: public CObjLine
{
public:
	CObjNoClimableLine();
	virtual ~CObjNoClimableLine();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

