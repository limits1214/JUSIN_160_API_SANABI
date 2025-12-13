#pragma once
#include "CObj.h"
#include "CCollisionEvent.h"
class CObjMonsterBullet :
    public CObj, public CCollisionEvent
{
public:
	CObjMonsterBullet();
	virtual ~CObjMonsterBullet();

	void Set_Angle(float fAngle)
	{
		m_fAngle = fAngle;
	}
	float Get_Angle()
	{
		return m_fAngle;
	}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) override;

	float m_fAngle;

	int m_iDeadTimer;

};

