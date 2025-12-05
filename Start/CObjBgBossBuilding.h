#pragma once
#include "CObj.h"
class CObjBgBossBuilding :
    public CObj
{
public:
	CObjBgBossBuilding();
	virtual ~CObjBgBossBuilding();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

