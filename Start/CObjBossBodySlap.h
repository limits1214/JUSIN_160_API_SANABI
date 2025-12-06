#pragma once
#include "CObj.h"
class CObjBossBodySlap: public CObj
{
public:
	CObjBossBodySlap();
	virtual ~CObjBossBodySlap();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

