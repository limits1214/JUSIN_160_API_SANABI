#pragma once
#include "CObj.h"
#include "CCollisionEvent.h"
class CObjBossBullet :
    public CObj, public CCollisionEvent
{
public:
	CObjBossBullet();
	virtual ~CObjBossBullet();

public:
	void Set_Option(int iOption)
	{
		m_iOption = iOption;
	}

	void Set_Angle(float fAngle)
	{
		m_fAngle = fAngle;
	}
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObj* pObj, COLLISIONID eCollID, void* = nullptr) override;

private:
	int m_iOption;
	float m_fAngle;
};

