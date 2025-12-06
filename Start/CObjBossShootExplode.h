#pragma once
#include "CObj.h"
class CObjBossShootExplode :
    public CObj
{
public:
	CObjBossShootExplode();
	virtual ~CObjBossShootExplode();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

