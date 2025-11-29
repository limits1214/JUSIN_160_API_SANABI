#pragma once
#include "CObj.h"
class CObjMonsterB: public CObj
{
public:
	CObjMonsterB();
	virtual ~CObjMonsterB();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

