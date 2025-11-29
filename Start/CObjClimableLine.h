#pragma once
#include "CObjLine.h"
class CObjClimableLine : public CObjLine
{
public:
	CObjClimableLine();
	virtual ~CObjClimableLine();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

