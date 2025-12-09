#pragma once
#include "CObj.h"
class CObjBgTutoMountain :
    public CObj
{
public:
	CObjBgTutoMountain();
	virtual ~CObjBgTutoMountain();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

