#pragma once
#include "CObj.h"
class CObjBossBodySlapAlert: public CObj
{
public:
	CObjBossBodySlapAlert();
	virtual ~CObjBossBodySlapAlert();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

