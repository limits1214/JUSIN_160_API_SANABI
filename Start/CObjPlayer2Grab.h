#pragma once
#include "CObj.h"
#include "CCollisionEvent.h"
class CObjPlayer2Grab: public CObj, public CCollisionEvent
{
public:
	CObjPlayer2Grab();
	virtual ~CObjPlayer2Grab();

public:
	bool Get_Ceiling()
	{
		return m_bCeiling;
	}

public:
	void Set_Radian(float fRadian)
	{
		m_fRadian = fRadian;
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

	void Set_GrabDir(DIRECTION eGrabDir)
	{
		m_eGrabDir = eGrabDir;
	}
	DIRECTION Get_GrabDir()
	{
		return m_eGrabDir;
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
	float m_fRadian;
	bool m_bCeiling;

	INFO m_tCollisionRectInfo;

	bool m_GrabSend;
	bool m_bCollisionLeft;
	bool m_bCollisionRight;

	int m_iCollisionOption;

	bool m_bMonsterExcSend;


	DIRECTION m_eGrabDir;
};

