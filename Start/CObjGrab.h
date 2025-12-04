#pragma once
#include "CObj.h"
#include "CCollisionEvent.h"
class CObjGrab : public CObj, public CCollisionEvent
{
public:
	CObjGrab();
	virtual ~CObjGrab();

public:
	bool Get_Ceiling()
	{
		return m_bCeiling;
	}

public:
	void Set_Angle(float fAngle)
	{
		m_fAngle = fAngle;
	}

	INFO Get_CollisionRectInfo()
	{
		return m_tCollisionRectInfo;
	}

	bool Get_CollisionLeft()
	{
		return m_bCollisionLeft;
	}

	bool Get_CollisionRight()
	{
		return m_bCollisionRight;
	}

	int Get_CollisionOption()
	{
		return m_iCollisionOption;
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
	float m_fAngle;
	bool m_bCeiling;

	INFO m_tCollisionRectInfo;

	bool m_GrabSend;
	bool m_bCollisionLeft;
	bool m_bCollisionRight;

	int m_iCollisionOption;


};

