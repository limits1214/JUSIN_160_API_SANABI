#pragma once

#include "CObj.h"
#include "CCollisionEvent.h"
#include "CObjMovable.h"

class CObjPlayer: public CCollisionEvent, public CObjMovable
{
//public:
//	enum STATE{IDLE, RUNNING, JUMP, ST_END};

public:
	CObjPlayer();
	virtual ~CObjPlayer();

public:
	void Set_PlayerState(FRAME_STATE_ID eState)
	{
		m_eCurState = eState;
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
	void _Move(DIRECTION eDir, float fDistance) override;

private:
	void Key_Input();
	void Motion_Change();
	void	Offset();



private:
	//STATE				m_ePreState;
	//STATE				m_eCurState;
	FRAME_STATE_ID m_ePreState;
	FRAME_STATE_ID m_eCurState;

	bool m_bJumpJustPressed;
};

