#pragma once
#include "CObj.h"
class CObjBossClusterAim: public CObj
{
public:
	CObjBossClusterAim();
	virtual ~CObjBossClusterAim();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	DWORD m_dwShootTime;
};

