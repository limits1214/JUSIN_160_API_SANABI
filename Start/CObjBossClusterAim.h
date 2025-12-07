#pragma once
#include "CObj.h"
class CObjBossClusterAim: public CObj
{
public:
	CObjBossClusterAim();
	virtual ~CObjBossClusterAim();

public:
	void Set_Shoot(bool bShoot)
	{
		m_bShoot = bShoot;
	}

public:
	void Shoot360ClusterBomblet();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	DWORD m_dwShootTime;

	bool m_bShoot;
};

