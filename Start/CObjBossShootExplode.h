#pragma once
#include "CObj.h"
#include "CCollisionEvent.h"
class CObjBossShootExplode :
    public CObj, public CCollisionEvent
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


public:
	void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) override;
};

